#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <utility>

using namespace std;

std::uniform_real_distribution<double> unif(0.0, 1.0);
std::default_random_engine re;

// win rate of a single rack of player1 = p1
// player1 race to race1
// player2 race to race2
map<pair<int,int>, double> play (double p1, int race1, int race2)
{
   const double p2 = 1 - p1;
   map<pair<int,int>, double> result;
   result[std::make_pair(0,0)] = 1.0;
   for(int i = 0; i <= race1; ++i)
      for( int j = 0; j <= race2; ++j)
      {
      	 if (i < race1)
	 result[std::make_pair(i,j)] += 
	    result[std::make_pair(i, j-1)]   *p2; 
	 
      	 if (j < race2)
	 result[std::make_pair(i,j)] += 
	    result[std::make_pair(i-1,   j)] *p1; 
      }
   return result;
}

// simulate possible result of one match
// win rate of a single rack of player1 = p1
// player1 race to race1
// player2 race to race2
pair<int,int> simOneMatch(double p1, int race1, int race2)
{
   for(int g1=0, g2=0; g1< race1 && g2<race2;)
   {
      if (unif(re) < p1) g1++;
      else g2++;

      if (g1==race1 || g2==race2){
	 return std::make_pair(g1,g2);
      }
   }

   throw 0;
}


// simulate result distribution
// win rate of a single rack of player1 = p1
// player1 race to race1
// player2 race to race2
// e.g. result[ <9, 5> ] = .3 means 30% chance to see 9:5 in a race to 9
map<pair<int,int>, double> playSim (int n_sim, double p1, int race1, int race2)
{
   map<pair<int,int>, double> result;

   for(int i = 0 ;i < n_sim; ++i)
   {
      result[simOneMatch(p1, race1, race2)] += 1.00/n_sim;
   }

   return result;
}

// f1: fargo rate of player1
// f2: fargo rate of player2
// return likelihood of win by player1 in a single rack
double pFargo(int f1, int f2)
{
   int diff = f1-f2;
   double mul = pow(2, diff/100.0);
   return mul / (1+mul);
}

int main(int argc, char* argv[])
{
   if (argc < 4)
   {
      cerr << "usage: " << argv[0] << 
	 " <fargo of player1> <fargo of player2>" <<
	 " <race>" << endl;

      exit(-1);
   }

   int fargo1 = stoi(argv[1]);
   int fargo2 = stoi(argv[2]);
   int race1  = stoi(argv[3]);
   int race2  = argc > 4 ? stoi(argv[4]) : race1;
   int n_sim  = argc > 5 ? stoi(argv[5]) : 99999 ;
   
   double p1 = pFargo(fargo1, fargo2);
   map<pair<int,int>, double> resultSim  = playSim(n_sim, p1, race1, race2);
   map<pair<int,int>, double> resultMath = play   (       p1, race1, race2);

   cout << setiosflags(std::ios::right) << setprecision(2); 
   double p_win1 = 0;
   for(int i = race1; i >=0; --i)
      for(int j = 0; j <=race2; ++j)
      {
	 if (i==race1 && j==race2) continue;

	 pair<int,int> score = std::make_pair(i,j);
	 double pctSim  = resultSim [score] * 100.0;
	 double pctMath = resultMath[score] * 100.0;
	 if (i==race1 || j ==race2)
	    cout << setw(2) << i << ":" << setw(2) << j << "\t"
	         << setw(5) << fixed << pctMath << "% (" 
		 << setw(5) << fixed << pctSim  << "% simulated)" << endl; 
	 if (i==race1) p_win1 += pctMath;
      }

   cout << endl << "P(Player 1 wins) = " << p_win1 << "%"<< endl << endl;

}
