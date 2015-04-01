#include <fstream>
#include <iostream>
#include <iomanip>
  
using namespace std;


int main() {
    ifstream in("input");
    ofstream out("output");
  
    unsigned int n;
    double c, f, x, seconds, production;

  
    in>>n;
  
    out<<fixed;
    out<<setprecision(7);
  
    for(unsigned int variant=0; variant<n; variant++) {
        in>>c>>f>>x;
        production = 2.0;
        seconds = 0.0;
      
        
        while(x/production > x/(production+f)+c/production) { 
            seconds += c/production;
            production += f;
        }
      
        seconds += x/production;
        
        out<<"Case #"<<variant+1<<": "<<seconds<<"\n";      
    }
  
    out.close();


    return 0;
}
