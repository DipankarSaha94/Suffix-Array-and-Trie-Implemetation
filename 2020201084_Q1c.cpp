#include<bits/stdc++.h>
#define ll long long

using namespace std;

bool comp(pair<int,pair<int,int>> pp1, pair<int,pair<int,int>> pp2){
    if(pp1.second.first == pp2.second.first){
        return (pp1.second.second < pp2.second.second);
    }
    else{
        return (pp1.second.first < pp2.second.first);
    }
}

vector<ll> buildSuffixArray(string str){
    vector<pair<int,pair<int,int>>> suffix(str.size());

    vector<ll> index(str.size());

    for(ll i=0;i<str.size();i++){
        ll frank=str[i]-'0';
        ll srank;
        if((i+1)<str.size())   srank=str[i+1]-'0';
        else srank=-1;
        suffix[i]={i,{frank,srank}};
    }

    sort(suffix.begin(), suffix.end(), comp);
	
	ll n = str.size();
    for(ll p=4;p<(n << 1);p <<= 2){
        ll rank=0;
        ll previous_rank=suffix[0].second.first;
        suffix[0].second.first=rank;
        index[suffix[0].first]=0;

        for(ll i=1;i<str.size();i++){
            if(suffix[i].second.first==previous_rank && suffix[i].second.second==suffix[i-1].second.second){
                previous_rank=suffix[i].second.first;
                suffix[i].second.first=rank;
            }
            else{
                rank++;
                previous_rank=suffix[i].second.first;
                suffix[i].second.first=rank;
            }
            index[suffix[i].first]=i;
        }
        for(ll i=0;i<str.size();i++){
            ll next_rank=suffix[i].first + p/2;
            if(next_rank<str.size()){
                suffix[i].second.second = suffix[index[next_rank]].second.first;
            }
            else{
                suffix[i].second.second = -1;
            }
        }
        sort(suffix.begin(), suffix.end(), comp);
    }

    vector<ll> suffix_vector;
    for(auto i : suffix){
    	suffix_vector.push_back(i.first);
	}
	
    return suffix_vector;
}

ll findPrefixSize(string a, string b){
    ll size=min(a.size(), b.size());
    ll count=0;
    for(ll i=0;i<size;i++){
        if(a[i]==b[i]){
            count++;
        }
        else {
        	return count;
		}
    }
    return count;
}

int main()
{
    string str;
    cin>>str;
	string str3 = str;
	reverse(str3.begin(),str3.end());
    string str2=str+'#'+str3;
    vector<ll> SuffixArr=buildSuffixArray(str2);
	vector<ll> LCP;
    LCP.push_back(0);
    for(int i =0;i<SuffixArr.size()-1;i++){
    	LCP.push_back(findPrefixSize(str2.substr(SuffixArr[i]),str2.substr(SuffixArr[i+1])));
	}
		
	ll longestlength = 0, Position = 0;
    for(int i=1;i<str2.length();++i)
    {
        if((LCP[i]>longestlength))
        {
            if((SuffixArr[i-1]<str.length() && SuffixArr[i]>str.length())||(SuffixArr[i]<str.length() && SuffixArr[i-1]>str.length()))
            {
                longestlength=LCP[i];
                Position=SuffixArr[i];
            }
        }
    }
	
	cout<<str2.substr(Position,longestlength)<<endl;

    return 0;
}
