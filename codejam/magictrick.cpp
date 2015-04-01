#include <fstream>
#include <iostream>
  
using namespace std;


int main() {
    ifstream in("input");
    ofstream out("output");
  
    unsigned int n, row, cards[4], skip, count, match,x;
  
    in>>n;
  
    for(unsigned int variant=1; variant <= n; variant++) {
      count = 0; 
      
      in>>row;  

      for(unsigned int i=0; i<4; i++) {
        if(i+1 == row) {
          for(unsigned int  j=0; j<4; j++) {
            in>>cards[j];
          }
        } else {
          for(unsigned int  j=0; j<4; j++) {
            in>>skip;
          }
        }
      }
      
      in>>row;
      
      for(unsigned int i=0; i<4; i++) {
        if(i+1 == row) {
          for(unsigned int  j=0; j<4; j++) {
            in>>x;
            
            cout<<x;
            
            for(unsigned int t=0; t<4; t++) {
              if(cards[t] == x) {
                count++;
                match = x;
              }
            }
          }

        } else {
          for(unsigned int  j=0; j<4; j++) {
            in>>skip;
          }
        }
      }
      
      out<<"Case #"<<variant<<": ";
      if(count == 0) {
        out<<"Volunteer cheated!"; 
      } else if(count == 1) {
        out<<match;
      } else {
        out<<"Bad magician!"; 
      }
      
      out<<"\n";
      
    }
  
    out.close();


    return 0;
}
