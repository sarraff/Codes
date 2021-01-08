/* Nishant Sarraff 
Using C++ language

Assumptions : 
1.As per the given article 
	If two sequences in an alignment share a common ancestor, mismatches can be interpreted as 
	Point mutations and Gaps
	A point mutation or substitution is a genetic mutation where a single nucleotide base is changed
	Means there is mis-match 

	And another one is Gaps, which is a genetic mutation where a single nucleotide base is destroyed
	Means a gap is created

	As per the given problem, I have assumed that we need total gap score between two sequences, 
	and we have to retrieve how the given two sequences can be aligned.


2. I have opted two appraoches, when I start aligning characters from back and when I start aligning characters from front
*/

#include<bits/stdc++.h>
typedef long long int ll;
using namespace std;

/* 
Logic:  Since, we need to find and add the gaps such that the given two sequences can be aligned
	 	And we need to add as many as less number of gaps as possible 
		
		The basic approach is that we will maintain a 'Gap Score' which will store counting of 
		gaps that have been added. And we will maintain a DP which will tell us that where we
		have added the gap. 

		Let's consider S1 is first sequence and S2 is second sequence
		For any S1[i] and S2[j], we have two options and three choices

		if S1[i] = S2[j] then we will not increase current 'Gap Score'
		if S1[i] != S2[j] then we will increase 'Gap Score' by 1 

		In case of S1[i] = S2[j], we don't need to add gap
		In case of S1[i] != S2[j], we need to add either gap in S1 sequence at ith position
			or we need to add gap in S2 sequence at jth position
		
		And here we will use DP such that it will consider only those gap that will lead to min 'Gap Score'
		If characters is different, DP[i][j] = min(DP[i-1][j] , DP[i][j-1])
			This means we will choose that option which have min 'Gap score' 

		If characters is same , DP[i][j]=DP[i-1][j-1] 
*/


void TopToBottom(string x,string y)
{
	ll m=x.size();
	ll n=y.size();
	ll DP[m+1][n+1]={0}; // initially Gap score is 0

	// In case when m=0 means there is no characters in x
	for(ll i=0;i<=n;i++)
		DP[0][i]=i;

	// In case, when n=0 means there is no character in y
	for(ll j=0;j<=m;j++)
		DP[j][0]=j;

	//Calculating the score
	for (ll i=1;i<=m; i++) 
	{ 
		for (ll j=1;j<=n;j++) 
		{ 
			if (x[i-1] == y[j-1]) 				//If same then previous score will be current score
				DP[i][j] = DP[i-1][j-1]; 
			else								//Else we will add 1 in minimum score
				DP[i][j] = min(DP[i-1][j] + 1 ,DP[i][j-1] + 1 ); 
		} 
	} 	 

	// Now, we have the minimum 'Gap Score' that can be possible
	// Now, we need to create our new aligned string
	// The basic approach that we followed to calculate min 'Gap score' was from top left to bottom right
	// Now, to construct string, we will move from bottom right to top left
	// At every step we will check two things, if S1[i]==S2[j] this means we will add these characters in our new string, S1new and S2new
	// If, S1[i]!=S2[j] this means we need to add gap, now check which value DP have taken, since DP[i][j]=min(DP[i-1][j]+1, DP[i][j-1]+1)
	// If DP[i][j] == 1+DP[i-1][j] means gap is added in S2new
	// If DP[i][j] == 1+DP[i][j-1] means gap is added in S1new

	string xnew="",ynew="";
	ll i=m,j=n;
	while(i>0 && j>0)
	{
		if(x[i-1] == y[j-1])
		{
			xnew.push_back(x[i-1]);
			ynew.push_back(y[j-1]);
			i--;
			j--;
		}
		else if(DP[i][j]== (1 + DP[i-1][j]))
		{
			xnew.push_back(x[i-1]);
			ynew.push_back((char)'_');
			i--;
		}
		else if(DP[i][j]== (1 + DP[i][j-1]))
		{
			xnew.push_back((char)'_');
			ynew.push_back(y[j-1]);
			j--;
		}
	}
	// If i>0 means S1 character is still there is not S2 character left means we need to add gaps in S2new
	while(i>0)
	{
		xnew.push_back(x[i-1]);
		ynew.push_back((char)'_');
		i--;
	}
	// If j>0 means S2 character is still there is not S1 character left means we need to add gaps in S1new
	while(j>0)
	{

		xnew.push_back((char)'_');
		ynew.push_back(y[j-1]);
		j--;
	}
	reverse(xnew.begin(), xnew.end()); // Since we are adding front last, we need to reverse the string
	reverse(ynew.begin(), ynew.end());
 
	cout << "[OUTPUT1]\nS1: "<<xnew<<"\nS2: "<<ynew<<"\nGap Score = "<<DP[m][n] << "\n";
	return;
}



/*In case of Bottom to Up approach we will simply start making string from front not from back*/

void BottomToUp(string x,string y)
{
	reverse(x.begin(), x.end());
	reverse(y.begin(), y.end());
	ll m=x.size();
	ll n=y.size();
	ll DP[m+1][n+1]={0}; // initially Gap score is 0

	for(ll i=0;i<=n;i++)
		DP[0][i]=i;

	for(ll j=0;j<=m;j++)
		DP[j][0]=j;

	for (ll i=1;i<=m; i++) 
	{ 
		for (ll j=1;j<=n;j++) 
		{ 
			if (x[i-1] == y[j-1]) 			
				DP[i][j] = DP[i-1][j-1]; 
			else								
				DP[i][j] = min(DP[i-1][j] + 1 ,DP[i][j-1] + 1 ); 
		} 
	} 	 
	string xnew="",ynew="";
	ll i=m,j=n;
	while(i>0 && j>0)
	{
		if(x[i-1] == y[j-1])
		{
			xnew.push_back(x[i-1]);
			ynew.push_back(y[j-1]);
			i--;
			j--;
		}
		else if(DP[i][j]== (1 + DP[i-1][j]))
		{
			xnew.push_back(x[i-1]);
			ynew.push_back((char)'_');
			i--;
		}
		else if(DP[i][j]== (1 + DP[i][j-1]))
		{
			xnew.push_back((char)'_');
			ynew.push_back(y[j-1]);
			j--;
		}
	}
	while(i>0)
	{
		xnew.push_back(x[i-1]);
		ynew.push_back((char)'_');
		i--;
	}
	while(j>0)
	{

		xnew.push_back((char)'_');
		ynew.push_back(y[j-1]);
		j--;
	}
	cout << "[OUTPUT2]\nS1: "<<xnew<<"\nS2: "<<ynew<<"\nGap Score = "<<DP[m][n] << "\n";
	return;
}


int main(){  
	string S1 = "FTFTALILLAVAV"; 
	string S2 = "FTALLLAAV"; 
	cout<<"[INPUT]\nS1 = ";cin>>S1;
	cout<<"S2 = ";cin>>S2;
	TopToBottom(S1,S2);
	BottomToUp(S1,S2);
	return 0; 
} 

