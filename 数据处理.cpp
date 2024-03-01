#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>

using namespace std;

double avg = 0;

double average(vector<double> vec, int num) {
	return double(accumulate(vec.begin(), vec.end(), 0.0)) / num;
}

double stddev(vector<double> vec, int num) {
	double avg = average(vec, num);
	double temp = 0;
	for (int i = 0; i < num; i++) temp += pow(vec[i] - avg, 2);
	return sqrt((temp / (num - 1)));
}

bool judge(double data, double g0, double stddev) {
	return data / stddev > g0 ? 1 : 0;
}

bool cmp(double a, double b) {
	return abs(a - avg) < abs(b - avg);
}

double finalStddev(double calStddev, double sysStddev) {
	return sqrt(pow(calStddev, 2) + pow(sysStddev, 2));
}

double no4yes6even5(double avg, double sigma) {
	int bitAfterSpot;
	if ((int)sigma != 0)
		cout << "误差整数部分应为0！";
	for (bitAfterSpot = 0; (int)sigma == 0; bitAfterSpot++)
		sigma *= 10;
	if (sigma > (int)sigma)
		sigma = (int)sigma + 1;
	int endWith5 = (int)(avg * pow(10, bitAfterSpot)) * 10 + 5;
	avg = (int)(avg * pow(10, bitAfterSpot + 1));
	if (avg < endWith5)
		return (int)(avg / 10) * pow(10, -bitAfterSpot);
	else if (avg > endWith5)
		return (int)(avg / 10) + 1 * pow(10, -bitAfterSpot);
	else {
		avg = (int)(avg / 10);
		if ((int)avg % 2)
			return (avg + 1) * pow(10, -bitAfterSpot);
		else
			return avg * pow(10, -bitAfterSpot);
	}
}

double plusBit(double sigma) {
	int bitAfterSpot;
	for (bitAfterSpot = 0; (int)sigma == 0; bitAfterSpot++)
		sigma *= 10;
	sigma = (int)sigma + 1;
	return sigma * pow(10, -bitAfterSpot);
}

int main()
{
	vector<double> data;
	int num = 0;
	double temp = 0;
	double g0 = 0;
	cout << "输入数据个数：\n";
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		cout << "输入第" << i + 1 << "个数据：";
		cin >> temp;
		data.push_back(temp);
	}
	avg = average(data, data.size());
	sort(data.begin(), data.end(), cmp);
	cout << "输入g0：";
	cin >> g0;
	while (judge(abs(data[data.size() - 1] - avg), g0, stddev(data, data.size())))
	{
		data.pop_back();
		avg = average(data, data.size());
	}
	double accAvg = average(data, data.size());
	double accStddev = stddev(data, data.size()) / sqrt(data.size());
	double instrumentError = 0;
	cout << "输入仪器误差：";
	cin >> instrumentError;
	double sysStddev = instrumentError / sqrt(3);
	double final_stddev = finalStddev(accStddev, sysStddev);
	cout << "平均值：" << fixed << setprecision(2) << no4yes6even5(accAvg) << endl;
	cout << "标准差：" << fixed << setprecision(2) << plusBit(final_stddev) << endl;
	//for (int i = 0; i < data.size(); i++) cout << data[i] << " ";
	return 0;
}