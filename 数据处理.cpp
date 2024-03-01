#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>

using namespace std;

double avg = 0;
double average(vector<double> vec, int num) {
	return double(accumulate(vec.begin(), vec.end(),0.0)) / num;
}
double stddev(vector<double> vec, int num) {
	double avg = average(vec,num);
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
int main()
{
	vector<double> data;
	int num = 0;
	double temp = 0;
	double g0 = 0;
	cout << "�������ݸ�����\n";
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		cout << "�����" << i + 1 << "�����ݣ�";
		cin >> temp;
		data.push_back(temp);
	}
	avg = average(data, data.size());
	sort(data.begin(), data.end(),cmp);
	cout << "����g0��";
	cin >> g0;
	while (judge(abs(data[data.size() - 1] - avg), g0, stddev(data, data.size())))
	{
		data.pop_back();
		avg = average(data, data.size());
	}
	double accAvg = average(data, data.size());
	double accStddev = stddev(data, data.size())/ sqrt(data.size());
	double instrumentError = 0;
	cout << "����������";
	cin >> instrumentError;
	double sysStddev = instrumentError / sqrt(3);
	double final_stddev = finalStddev(accStddev, sysStddev);
	cout << "ƽ��ֵ��" << fixed << setprecision(2) << accAvg << endl;
	cout << "��׼�" << fixed << setprecision(2) << final_stddev << endl;
	//for (int i = 0; i < data.size(); i++) cout << data[i] << " ";
	return 0;
}