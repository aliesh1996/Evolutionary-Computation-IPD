#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;



int chooseWithProbability(int option1, int option2, float probabilityOfOption1) {
    random_device rd;
    mt19937 eng(rd());
    uniform_real_distribution<float> distr(0, 1);

    if (distr(eng) <= probabilityOfOption1) {
        return option1;
    } else {
        return option2;
    }
}









int chooseOption(const vector<float>& probabilities) {
    random_device rd; 
    mt19937 gen(rd()); 
    uniform_real_distribution<> dis(0, 1);

    float random_number = dis(gen);
    float cumulative_probability = 0.0;

    for (size_t i = 0; i < probabilities.size(); ++i) {
        cumulative_probability += probabilities[i];
        if (random_number <= cumulative_probability) {
            return i; // Return the index of the chosen option
        }
    }

    return -1; // In case something goes wrong
}














float* game(int N, float genomes[N][2], int* history, float &pi_c){
  
    int prisoner[N];
    int collaboration[N];
    float scores[N];

    for(int i=0; i<N; i++){
        scores[i]=0.0;
    }
    

    srand(time(0));  // Initialize random number generator.
    int option1 = 1;
    int option2 = 0;
    float probabilityOfOption1;

    // cout<<genomes[0][0]<<endl;
    
    for(int i=0;i<N;i++){

        collaboration[i]=i;

    }


    // Define an array of integers

    int size = sizeof(collaboration) / sizeof(collaboration[0]);

    // Initialize a random number generator
    random_device rd;
    mt19937 g(rd());

    // Shuffle the array
    // shuffle(collaboration, collaboration + size, g);


    //the game
    ///changing the number of games randomly
    int updates = 10;
    float total=0;

    
    for(int j=0; j<updates; j++){

        float counter=0;
        shuffle(collaboration, collaboration + size, g);
        for(int i=0; i<N-1; i=i+2){

                if (history[collaboration[i+1]]==1){
                    probabilityOfOption1 = genomes[collaboration[i]][0]; 
                } else {
                    probabilityOfOption1 = genomes[collaboration[i]][1]; 
                }     
                    // cout<<probabilityOfOption1<<endl; 
                prisoner[collaboration[i]]=chooseWithProbability(option1, option2, probabilityOfOption1);

                if (history[collaboration[i]]==1){
                    probabilityOfOption1 = genomes[collaboration[i+1]][0]; 
                } else {
                    probabilityOfOption1 = genomes[collaboration[i+1]][1]; 
                }     
                    // cout<<probabilityOfOption1<<endl; 
                prisoner[collaboration[i+1]]=chooseWithProbability(option1, option2, probabilityOfOption1);
                


            if (prisoner[collaboration[i]]==1 && prisoner[collaboration[i+1]]==1){

                scores[collaboration[i]]+=(3.0/updates);
                scores[collaboration[i+1]]+=(3.0/updates);
                history[collaboration[i]]=1;
                history[collaboration[i+1]]=1;
                pi_c+=(1.0/(updates*N));
                pi_c+=(1.0/(updates*N));

                // cout<<"xxxxxxxxxxxxxxxxxxx";


            }else if (prisoner[collaboration[i]]==1 && prisoner[collaboration[i+1]]==0){

                scores[collaboration[i+1]]+=(5.0/updates);
                history[collaboration[i]]=1;
                history[collaboration[i+1]]=0;
                pi_c+=(1.0/(updates*N));
                // cout<<"111111111111111";
                

            }else if (prisoner[collaboration[i]]==0 && prisoner[collaboration[i+1]]==1){

                scores[collaboration[i]]+=(5.0/updates);
                history[collaboration[i]]=0;
                history[collaboration[i+1]]=1;
                pi_c+=(1.0/(updates*N));
                // cout<<"2222222222222222222222222";

            }else if (prisoner[collaboration[i]]==0 && prisoner[collaboration[i+1]]==0){

                scores[collaboration[i]]+=(1.0/updates);
                scores[collaboration[i+1]]+=(1.0/updates);
                history[collaboration[i]]=0;
                history[collaboration[i+1]]=0;
                // cout<<"3333333333333333333333333";
                // cout<<scores[collaboration[i]]<<endl;

            }

        }

    }

    // for(int k=0; k<N; k++){

    //     cout<<scores[k]<<endl;
    // }
    return scores; 
}




void fitness(int N, float* scores, float genomes[N][2], float* rands){

     

    float w[N];
    float W=0.0;
    float W2=0.0;
    int counter=0;
    vector<int> alive;
    vector<float> ws;

    float fitness=0;
    int chosen;
    float maxrand=0.0;
    float minrand=pow(1.1, 5);

    float avgscore=0.0;

    int scode[N];
    

    // for (int j=0; j<N; j++){
    //         cout<<scores[j]<<endl;
            

    //     }

    for(int i=0; i<N; i++){

        

        scode[i]=0;
        w[i]=pow(1.1, scores[i]);
        W+=w[i];

        
        
        avgscore+=(scores[i]/N);
        

        if (w[i]>maxrand){

            maxrand=w[i];
        }

        if (w[i]<minrand){

            minrand=w[i];
        }

    }

    



    cout<<avgscore<<endl;


    // random_device rd;
    // mt19937 rnd(rd());
    // uniform_real_distribution<float> distr(minrand/W, maxrand/W);

    // float rand = (minrand/W+maxrand/W)/2 ;

    // cout<<scores[0]<<endl;

    cout<<alive.size()<<endl;

    // int m=0;

    int xcounter=0;
    for(int l=0; l<N; l++){

        fitness=0;
       

        for(int i=0; i<N; i++){
        fitness += w[i]/W;

        // cout<<rand<<endl;
        // cout<<fitness<<endl; 

        // if(fitness<=rand){

        //     scode[i]=0;  
        //     // m++;
            
        // } else {

        //     alive.push_back(i);
        //     ws.push_back(fitness*W);
        //     W2+=fitness*W;
        //     counter++;


        // }

        if (fitness>rands[l]){

            alive.push_back(i);

            scode[l]=1;
            xcounter++;
            break;


        }

    } 


    }

    // cout<<xcounter<<endl;
    

    float overall=0;


    for(int i=0; i<counter; i++){

        ws[i]=ws[i]/W2;

        overall+=ws[i];
        
    }  

    if (overall!=1){       
        ws.push_back(1.0-overall);
        overall+=ws[counter];
    }

    cout<<alive.size()<<endl;
    // cout<<counter<<endl;
    // cout<<m<<endl;

    
    
    if(alive.size()>0){

        sort(alive.begin(), alive.end());

        
        

        for(int i=0; i<N; i++){ 

            // if(scode[i]==0){

                // cout<<alive[i]<<endl;
                // int chosen_option = chooseOption(ws);
                // cout<<chosen_option<<endl;

                // genomes[i][0]=genomes[alive[chosen_option]][0];
                // genomes[i][1]=genomes[alive[chosen_option]][1];

                genomes[i][0]=genomes[alive[i]][0];
                genomes[i][1]=genomes[alive[i]][1];
                // m++;
            }


            // } 

            // cout<<m<<endl; 
       
        
    } 


}







void mutation(float prob, string type, int N, float genomes[N][2]){

        if(type=="Normal"){

        random_device rd;
        mt19937 eng(rd());
        normal_distribution<float> distr(0, 0.2);

        for(int i=0; i<N; i++){

            for(int j=0; j<2; j++){

                int chosenOption = chooseWithProbability(1, 0, prob);

                if(chosenOption==1){

                float x1=genomes[i][j];


                x1+=distr(eng);

            if (x1<=1.0 && x1>=0.0){

                genomes[i][j]+=distr(eng);
            }

                }
              
            }

        }


    } else if(type=="Uniform"){

        random_device rd;
        mt19937 eng(rd());
        uniform_real_distribution<float> distr(0, 1);

        for(int i=0; i<N; i++){

            for(int j=0; j<2; j++){

                int chosenOption = chooseWithProbability(1, 0, prob);

                if(chosenOption==1){

                genomes[i][j]=distr(eng);

                }
            }         
        }
    }
}











int main(){

//creating the random population

    int N=100;

    int generations=100;

    float genomes[N][2];

    int history[N];

    float x[N];

    float p1[generations];
    float p2[generations];
    float p_c[generations];

    random_device rd;
    mt19937 eng(rd());
    uniform_real_distribution<float> distr(0, 1);

    for (int i=0; i<N; i++){

        genomes[i][0] = distr(eng);
        // genomes[i][0]=1.0;
        x[i]=genomes[i][0];
        genomes[i][1] = distr(eng);
        // genomes[i][1]=1.0;
        history[i] = 1;

        
    }

    for (int i=0; i<generations; i++){

        p1[i]=0.0;
        p2[i]=0.0;
        p_c[i]=0.0;
    }

    

    for(int g=0; g<generations; g++){

        cout<<"running at: "<<g<<endl;

        for (int i=0; i<N; i++){

        x[i]=genomes[i][0];


        
        }
        
        float pi_c=0.0;
        float* scores=game(N, genomes, history, pi_c);

        // for (int j=0; j<N; j++){
        //     cout<<scores[j]<<endl;
            

        // }

        float rands[N];

        for(int s=0; s<N; s++){

            rands[s]=distr(eng);


        }

        fitness(N, scores, genomes, rands);
        // mutation(0.1, "Uniform", N, genomes);


        // cout<<pi_c<<endl;
        p_c[g]=pi_c;
        
        int inequal=0;
        for (int j=0; j<N; j++){

            p1[g]+=(genomes[j][0]/N);
            p2[g]+=(genomes[j][1]/N);

            
            if (genomes[j][0]!=x[j]){



                inequal++;
            }
            

        }
        cout<<inequal<<endl;
    }

    int gencounter[generations];

    for (int j=0; j<generations; j++){

        // cout<<p1[j]<<endl;
        gencounter[j]=j;
    }

    ofstream file("p1.csv");

    if (file.is_open()) {
        // Assuming you are writing some x and y data points
        for (int i = 0; i < generations; ++i) {
            double x = gencounter[i]; // your data for x
            double y = p1[i]; // example data for y, e.g., y = x^2
            file << x << "," << y << "\n";
        }
        file.close();
    } else {
        cout << "Unable to open file";
    }


    ofstream file2("p2.csv");

    if (file2.is_open()) {
        // Assuming you are writing some x and y data points
        for (int i = 0; i < generations; ++i) {
            double x2 = gencounter[i]; // your data for x
            double y2 = p2[i]; // example data for y, e.g., y = x^2
            file2 << x2 << "," << y2 << "\n";
        }
        file2.close();
    } else {
        cout << "Unable to open file";
    }


     ofstream file3("p_c.csv");

    if (file3.is_open()) {
        // Assuming you are writing some x and y data points
        for (int i = 0; i < generations; ++i) {
            double x2 = gencounter[i]; // your data for x
            double y2 = p_c[i]; // example data for y, e.g., y = x^2
            file3 << x2 << "," << y2 << "\n";
        }
        file3.close();
    } else {
        cout << "Unable to open file";
    }



    return 0;

}










