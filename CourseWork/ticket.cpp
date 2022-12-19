#include "ticket.h"

std::wstring utf8_decode(const std::wstring& instr) {
	const std::string str(instr.begin(), instr.end());
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

std::string unicode2ansi(const std::wstring& wstr) {
	int size_needed = WideCharToMultiByte(CP_ACP, 0, &wstr[0], -1, NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_ACP, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	strTo.pop_back();
	return strTo;
}

/*bool operator<(const varsS& a, const varsS& b) { return a.diff < b.diff; }
bool operator==(const varsS& a, const varsS& b) { return a.str == b.str && a.diff == b.diff; }
bool operator!=(const varsS& a, const varsS& b) { return a.str != b.str && a.diff != b.diff; }
void operator-=(std::vector<varsS>& a, const std::vector<varsS>& b)
{
	std::vector<varsS>::iterator it = a.begin();
	std::vector<varsS>::const_iterator it2 = b.begin();

	while (it != a.end()) {
		while (it2 != b.end() && it != a.end()) {
			if (*it == *it2) {
				it = a.erase(it);
				it2 = b.begin();
			}
			else
				++it2;
		}
		if (it != a.end()) ++it;
		it2 = b.begin();
	}
} */

void ticket::inputv(const int& vin) {
	vQ = vin;
}

void ticket::inputq(const int& qin) {
	qQ = qin;
}

void ticket::input() {
	vars.clear();
	isHard = false;
}

void ticket::input(const std::string inpath) {
	std::wifstream fin(inpath);
	isHard = false;

	varsS initial;
	std::wstring inTmp;
	int hardPos, coun = 0;
	if (fin.is_open()) {
		while (getline(fin, inTmp)) {
			vars.push_back(initial);
			hardPos = hardness(std::wstring(inTmp));
			if (hardPos) {
				isHard = true;
				vars.at(coun).diff = std::stoi(&inTmp[hardPos + 2]);
				inTmp.erase(inTmp.begin() + hardPos, inTmp.begin() + hardPos + 3);
			}
			else {
				vars.at(coun).diff = 6;
			};

			vars.at(coun).str = inTmp;
			++coun;
		}
		fin.close();
	}
	else MessageBox::Show(L"Ошибка открытия файла ввода!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
}

int ticket::hardness(const std::wstring& in) {
	std::wregex temp(L"\ ![1-5]");
	std::wsregex_iterator find{ in.begin(), in.end(), temp };
	std::wsregex_iterator end{};

	for (auto i = find; i != end; ++i) return i->position();
	return 0;
}

void ticket::output(const char& outm) {
	outmode[0] = outm;
}

int ticket::output()
{
	return vars.size();
}

void ticket::output(const std::vector<varsS>& vec) {
	int coun = 0, counv = 0;
	if (outmode[0] == 'r') {
		std::ofstream fout("Sorted.rtf");

		if (fout.is_open()) {
			for (const varsS& i : vec) {
				if (!i.diff) {
					counv++;
					fout << std::endl << "Вариант " << counv << ":" << std::endl;
					coun = 0;
				}
				else {
					++coun;
					fout << coun << (". ") << unicode2ansi(utf8_decode(i.str));
					if (isHard) fout << " : " << i.diff;
					fout << std::endl;
				}
			}
			fout.close();
		}
		else MessageBox::Show(L"Ошибка открытия файла вывода!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else {
		std::wofstream fout("Sorted.txt");

		if (fout.is_open()) {
			for (const varsS& i : vec) {
				if (!i.diff) {
					counv++;
					fout << std::endl << L"ÐÐ°ÑÐ¸Ð°Ð½Ñ " << counv << L":" << std::endl;
					coun = 0;
				}
				else {
					++coun;
					fout << coun << L". " << i.str;
					if (isHard) fout << L" : " << i.diff;
					fout << std::endl;
				}
			}
			fout.close();
		}
		else MessageBox::Show(L"Ошибка открытия файла вывода!", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

void ticket::dumbsortfout() {
	std::vector <varsS> sorted, inp = vars;
	varsS null{ null.diff = 0 };
	std::stable_sort(inp.begin(), inp.end());

	for (int i = 0; i < vQ; ++i) {
		if (!inp.size()) break;

		sorted.push_back(null);

		if (inp.size() < qQ) {
			for (const varsS& i : inp) sorted.push_back(i);
			inp.clear();
			break;
		};

		for (int k = 0; k < qQ; ++k) {
			sorted.push_back(inp[0]);
			inp.erase(inp.begin());
		}
	}

	output(sorted);
}

void ticket::randsortfout() {
	std::vector <varsS> sorted;
	std::vector <varsS> used;
	varsS null{ null.diff = 0 };
	varsS it;

	for (int i = 0; i < vQ; ++i) {
		sorted.push_back(null);
		used.clear();
		for (int k = i * vQ; k < i * vQ + qQ; ++k) {
			it = vars_substr_vec(used, k);
			sorted.push_back(it);
			used.push_back(it);
		}
	}

	output(sorted);
}

varsS ticket::vars_substr_vec(std::vector<varsS>& used, const int& seed) {
	std::vector <varsS> vec = vars;

	if (used.size())vec -= used;

	srand(unsigned(time(NULL)) + seed);
	return vec[(rand() % vec.size() + 1) - 1];
}

void ticket::balancesortfout() {
	std::vector <varsS> sorted, used, in = vars;
	varsS used1elem;
	varsS null{ null.diff = 0 };

	for (int i = in.size(); i <= qQ * vQ; ++i) {
		in.push_back(vars_substr_vec(used, i));
	}

	stable_sort(in.rbegin(), in.rend());

	int mid = 0;
	for (const varsS& i : in) {
		mid += i.diff;
	}
	mid = ceil((mid + .0) / vQ);

	int tmp;
	for (int i = 0; i < vQ; ++i) {
		if (i) used1elem = used[0];
		tmp = 0, used.clear();

		if (!in.size()) break;

		sorted.push_back(null);

		for (int k = 0; k < in.size(); ++k) {
			if ((tmp + in.at(k).diff <= mid) && (std::find(used.begin(), used.end(), in[k]) == used.end())) {
				if (i && in[k] == used1elem) continue;
				used.push_back(in[k]);
				tmp += in.at(k).diff;
				sorted.push_back(in[k]);
				in.erase(in.begin() + k);
			}
		}
	}

	output(sorted);
}

bool ticket::hardness() {
	return isHard;
}