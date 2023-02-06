#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#include <stdio.h>

using namespace std;

double sumOfNumericVector(vector<double> aNumericVector) {
	double sum = 0;
	for (int i = 0; i < aNumericVector.size(); i++) {
		sum += aNumericVector[i];
	}
	
	return sum;
}

double meanOfNumericVector(vector<double> aNumericVector, int numberOfObservations) {
	double sum = sumOfNumericVector(aNumericVector);
	double mean = sum / numberOfObservations;
	return mean;
}

double medianOfNumericVector(vector<double> aNumericVector, int numberOfObservations) {
	double median = 0;
	sort(aNumericVector.begin(), aNumericVector.end());
	if (numberOfObservations % 2 == 0) {
		double top = (numberOfObservations + 1) / 2;
		double bottom = numberOfObservations / 2;
		median = (aNumericVector[bottom] + aNumericVector[top]) / 2;
	}
	else {
		median = aNumericVector[(numberOfObservations + 1) / 2];
	}
	return median;
}

double rangeOfNumericVector(vector<double> aNumericVector, int numberOfObservations) {
	double range = 0;
	sort(aNumericVector.begin(), aNumericVector.end());
	range = aNumericVector[numberOfObservations - 1] - aNumericVector[0];
	return range;
}

double covar(vector<double> rm, vector<double> medv) {
	double covariance = 0;
	for (int i = 0; i < rm.size(); i++) {
		covariance += ((rm[i] - meanOfNumericVector(rm, rm.size())) * (medv[i] - meanOfNumericVector(medv, rm.size()))) / (rm.size() - 1);
	}
	return covariance;
}

double cor(vector<double> rm, vector<double> medv) {
	double correlation = 0;
	double std1 = 0, std2 = 0;

	for (int i = 0; i < rm.size(); i++) {
		std1 += ((rm[i] - meanOfNumericVector(rm, rm.size())) * (rm[i] - meanOfNumericVector(rm, rm.size()))) / (rm.size());
	}

	for (int j = 0; j < medv.size(); j++) {
		std2 += ((medv[j] - meanOfNumericVector(medv, medv.size())) * (medv[j] - meanOfNumericVector(medv, medv.size()))) / (medv.size());
	}
	
	correlation = covar(rm, medv) / ((sqrt(std1)) * (sqrt(std2)));
	return correlation;
}

void print_stats(vector<double> aNumericVector) {
	cout << "Sum: " << sumOfNumericVector(aNumericVector) << endl;
	cout << "Mean: " << meanOfNumericVector(aNumericVector, aNumericVector.size()) << endl;
	cout << "Median: " << medianOfNumericVector(aNumericVector, aNumericVector.size()) << endl;
	cout << "Range: " << rangeOfNumericVector(aNumericVector, aNumericVector.size()) << endl;
}

int main(int argc, char** argv) {

	ifstream inFS;
	string line;
	string rm_in, medv_in;
	const int MAX_LEN = 1000;
	vector<double> rm(MAX_LEN);
	vector<double> medv(MAX_LEN);
	
	
	//try to open file
	cout << "Opening file Boston.csv" << endl;

	inFS.open("Boston.csv");
	if (!inFS.is_open()) {
		cout << "Could not open file Boston.csv" << endl;
		return 1; //1 indicates error
	}

	//can now use inFS stream like cin stream
	//Boston.csv should contain two doubles

	cout << "Reading line 1" << endl;
	getline(inFS, line);
	
	//echo heading
	cout << "heading: " << line << endl;

	int numObservations = 0;
	while (inFS.good()) {

		getline(inFS, rm_in, ',');
		getline(inFS, medv_in, '\n');

		rm.at(numObservations) = stof(rm_in);
		medv.at(numObservations) = stof(medv_in);

		numObservations++;
	}

	rm.resize(numObservations);
	medv.resize(numObservations);

	cout << "new length " << rm.size() << endl;

	cout << "Closing file Boston.csv" << endl;
	inFS.close();//done with file, so close it

	cout << "Number of records: " << numObservations << endl;

	cout << "\nStats for rm" << endl;
	print_stats(rm);

	cout << "\nStats for medv" << endl;
	print_stats(medv);

	cout << "\n Covariance = " << covar(rm, medv) << endl;
	cout << "\n Correlation = " << cor(rm, medv) << endl;
	cout << "\nProgram terminated.";

	return 0;
}