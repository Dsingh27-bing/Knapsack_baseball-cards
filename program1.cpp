#include <fstream>
#include <cstdio>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <tuple>
#include <cstdlib>
#include <algorithm>
#include <bitset>
#include <cstring>
#include <sstream>
#include <numeric>
#include <ctime>
using namespace std;


vector<pair<string, int>> market;
vector<pair<string, int>> priceList;
int marketItems = 0;
int currentItems = 0;
int currentBudget = 0;
vector <int> all_items;
vector <int> max_diff_subset;



int computeProfit(pair <string, int> input_pairs, vector<pair<string, int>> market_pairs, int market_size){
  int profit = 0;
  for (int i = 0; i<market_size; ++i){
    if (input_pairs.first.compare(market_pairs[i].first)==0){
      profit = market_pairs[i].second - input_pairs.second;
      all_items.push_back(i);
    }
  }

  return profit;

}


void main_function(vector<pair<string, int>> market_pairs, vector<pair<string, int>> input_pairs, int weight)
{

    

//ofstream outfile("output.txt");

//define the output file stream
std::ofstream outfile("output.txt",ios::app);
	
    // redirect the output stream to outfile
streambuf *coutbuf = std::cout.rdbuf();
cout.rdbuf(outfile.rdbuf());

    // find the subset with maximum difference
    int max_profit=0;
    // vector<int> max_diff_subset;
    std::clock_t start = std::clock(); // get the start time
    // check if the sum of all integer values is less than or equal to weight

    int sum = 0;
    for (int i = 0; i<currentItems; ++i){
      // cout<< input_pairs[i].second << "  second" <<endl;
      sum += input_pairs[i].second;
    }

    //cout << "sum" << sum << endl;

    if (sum <= weight) {
      // all prices are within budget
        //cout<<weight<<"\t in\n";
        for (int j = 0; j < currentItems; j++) {
            max_profit += computeProfit(input_pairs[j], market_pairs, marketItems);
            }
        max_diff_subset = all_items;
        }
    else{
      // prices of all items are beyond budget, create subsets and compare prices
      for (int i = 0; i< (1<<currentItems); ++i){
        vector <int> subset;
        int profit = 0;
        sum = 0;
        all_items.clear();
        for (int j =0; j <currentItems; ++j){
          if ((i & (1 <<j))!=0){
            profit += computeProfit(input_pairs[j], market_pairs, marketItems);
            sum += input_pairs[j].second;
          }
        }
        //cout <<"profit" << profit <<endl;
        //cout << "sum" <<sum<<endl;
        if (profit > max_profit && sum<=currentBudget){
          max_profit = profit;
          max_diff_subset = all_items;
        }
      }
    }

  // currentItems max_profit max_diff_subset.size() clocktime
  //below for printing results
  

    std::clock_t end = std::clock(); // get the end time
    double elapsed_time = static_cast<double>(end - start) /CLOCKS_PER_SEC; // calculate the elapsed time
    std::cout << currentItems<<" "<<max_profit<<" "<<" "<<max_diff_subset.size()<< elapsed_time  << std::endl; // printing output 4
    for (int i = 0; i<int(max_diff_subset.size()); ++i){
    cout << market[max_diff_subset[i]].first << endl;
  }

   

}

void openMarket(char* argv[]){
    int count = 0;
    ifstream infile(argv[2]);
    string line;


    while (getline(infile, line)) {
      if (!count){
        ++count;
        istringstream iss(line);
        iss >> marketItems;
        // cout <<marketItems <<endl;
        continue;
      }
      else{
        string itemName;
        int itemPrice;
        istringstream iss(line);
        iss >> itemName>>itemPrice;
        // cout <<itemName << endl << "hello" << itemPrice<<endl;
        market.emplace_back(itemName,itemPrice);
      }
      // cout << line << endl;
    }

    infile.close();


}


int main(int argc, char* argv[]) {

	std::remove("output.txt");
  if (argc <5){
    cout << "error in arguments";
    exit(0);
  }
  if ((!strcmp(argv[3], "-p") && !(strcmp(argv[1], "-p"))) || ((!strcmp(argv[3], "-m") && !(strcmp(argv[1], "-m"))))){
    cout<<"ERROR in arguments";}

    if (!strcmp(argv[3], "-m") || !(strcmp(argv[1], "-m"))){
      openMarket(argv);
    }

    if (!strcmp(argv[3], "-p") || !(strcmp(argv[1], "-p"))){
      int count = 0;
      ifstream pricefile(argv[4]);
      string line;
      

      while (getline(pricefile, line)) {
        if (!count){
          ++count;
          priceList.clear();
          max_diff_subset.clear();
          istringstream iss(line);
          iss >> currentItems >> currentBudget;
          // cout <<currentItems << "\t" << currentBudget<< endl;
          continue;
        }
        else{

          if (count <=currentItems){
            string itemName;
            int itemPrice;
            istringstream iss(line);
            iss >> itemName>>itemPrice;
            // cout <<itemName << endl << "hello" << itemPrice<<endl;
            priceList.emplace_back(itemName,itemPrice);
            ++count;

          }
          if (count > currentItems){
            // for (int i = 0; i<currentItems; ++i){
            //   // cout <<i << "   "<< currentItems <<endl;
            //   cout << priceList[i].first << "    "<< priceList[i].second <<endl;
            // }
            count = 0;
            main_function(market, priceList, currentBudget);
          }


        }
        // cout << line << endl;
      }

      pricefile.close();
    }

    return 0;

  }
