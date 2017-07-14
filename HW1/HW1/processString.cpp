#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include <gtest\gtest.h>

using namespace std;


// getAscendingStr Function requirement
//
// Take space seperated digit string (ex. "1 2 3 5 4") and 
//   modify input string to ascending order ("1 2 3 4 5").
//
// return 0 if success, (empty string)
//       -1 if exception occur (ex. string containing non-digit character)
int getAscendingStr(string& inputStr)
{
	/// Please fill your code here

	int arr[10];
	int subStringCnt =0;
	//double d;
	//char c;

	stringstream tmpString(inputStr);
	stringstream changeString;
	//stringstream cmpString;
	string subString;
	while (getline(tmpString, subString, ' '))   //把inputStr 利用空格分割並存在 subString
	{
		stringstream cmpString(subString);          //判斷subString是否為數字,若否,則return -1
		double d;
		char c;
		if (!(cmpString >> d))
		{
			return -1;
		}
		if (cmpString >> c)
		{
			return -1;
		}

		arr[subStringCnt]=atoi(subString.c_str());  //subString 為數字,存入array等待sorting
		subStringCnt++;
	}

	sort(arr, arr + subStringCnt);

	/*for (int i = 0; i < subStringCnt; i++)
	{
		cout << "Num:" << i << " is " << arr[i] << endl;
	}*/
	
	changeString << arr[0];
	changeString >> subString;
	inputStr = subString;

	for (int i=1; i<subStringCnt; i++)   //把切割出的數字轉成字串再串接起來
	{
		changeString.str("");
		changeString.clear();
		changeString << arr[i];
		changeString >> subString;
		inputStr = inputStr + " " + subString;
	}

	return 0;
}

// solveQ Function requirement
// 
// solve quadratic function ax^2 + bx + c = 0
//
// return 1 if equation has two different real number root 
//          (return vector size should be 2 containing 2 solution.  
//          Greater value should put into smaller vector index)
//        0 there is only one possible solution to the quadratic equation 
//          (return vector size should be 1)
//       -1 complex roots 
//          (return vector size should be 0)
int solveQ(vector<double> &x, double a, double b, double c)
{
	int delta = ((b*b) - (4 * a*c));

	if (delta > 0)
	{
		int solve1 = ((((-1)*b) + sqrt(delta)) / (2 * a));
		int solve2 = ((((-1)*b) - sqrt(delta)) / (2 * a));
		x.push_back(solve1);
		x.push_back(solve2);

		return 1;
	}
	else if (delta == 0)
	{
		int solve1 = ((((-1)*b) + sqrt(delta)) / (2 * a));
		x.push_back(solve1);
		return 0;
	}
	else
	{

		return -1;
	}

	return 0;
}

int main(int argc, char*argv[]) {
	
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}

TEST(getAscendingStr, SimpleAscending)
{//Simple ascending test case

	string inputStr = "1 -3 2195 4 50";
	string tmpStr = inputStr;
	int err = getAscendingStr(tmpStr);
	EXPECT_EQ(tmpStr, "-3 1 4 50 2195");
	EXPECT_EQ(err, 0);
}

TEST(getAscendingStr, handleNonDigit)
{//getAscendingStr function should handle non digit case
	string tmpStr = "1 3 2 4 a 7f415";
	int err = getAscendingStr(tmpStr);
	EXPECT_EQ(err, -1);
}

TEST(solveQ, twoSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, 2, -3);
	EXPECT_EQ(iSol, 1);
	EXPECT_EQ(sol.size(), 2);
	EXPECT_EQ(sol.at(0), 1);
	EXPECT_EQ(sol.at(1), -3);
}

TEST(solveQ, oneSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, -8, 16);
	EXPECT_EQ(iSol, 0);
	EXPECT_EQ(sol.size(), 1);
	EXPECT_EQ(sol.at(0), 4);
}

TEST(solveQ, noSolution)
{
	vector<double> sol;
	int iSol = solveQ(sol, 1, 1, 16);
	EXPECT_EQ(iSol, -1);
	EXPECT_EQ(sol.size(), 0);
}