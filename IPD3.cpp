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





vector<vector<int> > roundRobin(vector<int> players) {
    int numPlayers = players.size();
    bool isOdd = numPlayers % 2 != 0;
    vector<int> modPlayers = players;

    random_device rd;
    mt19937 g(rd());
    uniform_real_distribution<> dis(0, 1);

    if (isOdd) {
        modPlayers.push_back(-1); // Add a placeholder for odd number of players
        ++numPlayers;
    }

    vector<vector<int> > final_competition;

    

    float random = 0.3;

    for (int round = 1; round < numPlayers; ++round) {

        // cout<<"random: "<<random<<"\n";

        if (random>0.1){

            // cout << "Round " << round << ":\n";
            vector<int> competition;
            

            for (int i = 0; i < numPlayers / 2; ++i) {
                int player1 = modPlayers[i];
                int player2 = modPlayers[numPlayers - i - 1];

                competition.push_back(player1);
                competition.push_back(player2);


                // if (player1 != -1 && player2 != -1) {
                //     cout << "  " << player1 << " vs " << player2 << "\n";
                // }
            }
            // Rotate players for the next round, except the first player
            rotate(modPlayers.begin() + 1, modPlayers.begin() + 2, modPlayers.end());
            final_competition.push_back(competition);
        }else{

            break;
        }

        random = dis(g);
        


        }
        

    return final_competition;
}







void game(int N, float genomes[N][2], int* history, float &pi_c, float* scores){
  
    int prisoner[N];
    vector<int> collaboration;
    

    srand(time(0));  // Initialize random number generator.
    int option1 = 1;
    int option2 = 0;
    float probabilityOfOption1;

    // cout<<genomes[0][0]<<endl;
    
    for(int i=0;i<N;i++){

        collaboration.push_back(i);

    }


    //the game
    ///changing the number of games randomly
    int updates = 0;
    float total=0;

    float random = 0.2;

    int player = 0;

    vector<vector<int> > competition=roundRobin(collaboration);


    float counter=0;
    updates = competition.size()*20;

    // cout<<updates<<endl;
    // cout<<competition[0].size()<<endl;

    for(int c=0; c<competition.size(); c++){

        // cout<<"round:"<<c<<endl;

        for(int i=0; i<N-1; i=i+2){

            // cout<<competition[c][i]<<" vs "<<competition[c][i+1]<<endl;

            for(int t=0; t<20; ++t){

                // cout<<"the historical move:"<<history[competition[c][i+1]];


                if (history[competition[c][i+1]]==1){
                    probabilityOfOption1 = genomes[competition[c][i]][0]; 
                } else {
                    probabilityOfOption1 = genomes[competition[c][i]][1]; 
                }     
                        // cout<<probabilityOfOption1<<endl; 
                prisoner[competition[c][i]]=chooseWithProbability(option1, option2, probabilityOfOption1);

                if (history[competition[c][i]]==1){
                    probabilityOfOption1 = genomes[competition[c][i+1]][0]; 
                } else {
                    probabilityOfOption1 = genomes[competition[c][i+1]][1]; 
                }     
                        // cout<<probabilityOfOption1<<endl; 
                prisoner[competition[c][i+1]]=chooseWithProbability(option1, option2, probabilityOfOption1);
                    
                
                

                if (prisoner[competition[c][i]]==1 && prisoner[competition[c][i+1]]==1){

                    scores[competition[c][i]]+=3.0;
                    scores[competition[c][i+1]]+=3.0;
                    history[competition[c][i]]=1;
                    history[competition[c][i+1]]=1;
                    pi_c+=(1.0/N);
                    pi_c+=(1.0/N);

                    // cout<<"xxxxxxxxxxxxxxxxxxx";


                }else if (prisoner[competition[c][i]]==1 && prisoner[competition[c][i+1]]==0){

                    scores[competition[c][i+1]]+=5.0;
                    history[competition[c][i]]=1;
                    history[competition[c][i+1]]=0;
                    pi_c+=(1.0/N);
                    // cout<<"111111111111111";
                    

                }else if (prisoner[competition[c][i]]==0 && prisoner[competition[c][i+1]]==1){

                    scores[competition[c][i]]+=5.0;
                    history[competition[c][i]]=0;
                    history[competition[c][i+1]]=1;
                    pi_c+=(1.0/N);
                    // cout<<"2222222222222222222222222";

                }else if (prisoner[competition[c][i]]==0 && prisoner[competition[c][i+1]]==0){

                    scores[competition[c][i]]+=1.0;
                    scores[competition[c][i+1]]+=1.0;
                    history[competition[c][i]]=0;
                    history[competition[c][i+1]]=0;
                    // cout<<"3333333333333333333333333";
                    // cout<<scores[collaboration[i]]<<endl;

                }


            }

            

        }


    }
    



    // cout<<random<<endl;
    // cout<<updates<<endl;

    for(int k=0; k<N; k++){


        scores[k]=scores[k]/updates;
        // cout<<scores[k]<<endl;

        
    }
    pi_c=pi_c/updates;

    
}












void fitness(int N, float* scores, float genomes[N][2], float* rands, double &avgscore){


    float w[N];
    float W=0.0;
    float W2=0.0;
    int counter=0;
    int alives[N];
    vector<int> alive;
    vector<float> ws;
    int xxcounter[N];

    float fitness=0;
    int chosen;

    

    // for (int j=0; j<N; j++){
    //         cout<<scores[j]<<endl;
            

    //     }

    for(int i=0; i<N; i++){

        xxcounter[i]=0;
        w[i]=pow(1.1, scores[i]);
        W+=w[i];

        // cout<<N<<endl;

        
        avgscore+=scores[i]/N;

    }

    
    cout<<avgscore<<endl;

    int xcounter=0;
    for(int l=0; l<N; l++){

        fitness=0;
       

        for(int i=0; i<N; i++){
        fitness += w[i]/W;

        if (fitness>rands[l]){

            alive.push_back(i);

            if (xxcounter[i]==0){
                xxcounter[i]=1;
                xcounter++;
            }

            
            break;


        }

    } 


    }

    float newgen[N][2];

    
    
    if(alive.size()>0){
        

        for(int i=0; i<N; i++){ 

                newgen[i][0]=genomes[alive[i]][0];
                newgen[i][1]=genomes[alive[i]][1];

            }

            for(int i=0; i<N; i++){ 

                genomes[i][0]=newgen[i][0];
                genomes[i][1]=newgen[i][1];
            }
       
        
    } 

    


}













void mutation(float prob, string type, int N, float genomes[N][2]){

        int counter = 0;

        if(type=="Normal"){

        random_device rd;
        mt19937 eng(rd());
        normal_distribution<float> distr(0, 1);

        float rand2;

        for(int i=0; i<N; i++){

            for(int j=0; j<2; j++){

                int chosenOption = chooseWithProbability(1, 0, prob);

                if(chosenOption==1){

                float x1=genomes[i][j];

                x1=distr(eng);

            if (x1<=1.0 && x1>=0.0){

                genomes[i][j]+=x1;
            } else {

                int z1 = x1;

                float z2 = x1-z1;

                    genomes[i][j]+=z2;

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
                counter++;

                }
            }         
        }
    }

    cout<<counter<<endl;
}











int main(){

//creating the random population

    int N=100;

    int generations=1000;

    float genomes[N][2];

    int history[N];

    float x[N];

    float p1[generations];
    float p2[generations];
    float p_c[generations];

    int selection[generations];
    float evaluator[generations];
    float averagescore[generations];
    float avgpayoff[generations];

    random_device rd;
    mt19937 eng(rd());
    uniform_real_distribution<float> distr(0, 1);

    for (int i=0; i<N; i++){

        genomes[i][0] = distr(eng);
        x[i]=genomes[i][0];
        genomes[i][1] = distr(eng);
        history[i] = chooseWithProbability(1, 0, 0.5);

        
    }

    // for (int i=0; i<N; i++){

    //     if(i<200){

    //         genomes[i][0] = 1.0;
    //         x[i]=genomes[i][0];
    //         genomes[i][1] = 0.0;
    //         history[i] = 1;


    //     }else{

    //         genomes[i][0] = 1.0;
    //         x[i]=genomes[i][0];
    //         genomes[i][1] = 1.0;
    //         history[i] = 1;


    //     }
        
    // }

    for (int i=0; i<generations; i++){

        p1[i]=0.0;
        p2[i]=0.0;
        p_c[i]=0.0;
        selection[i]=0;
        evaluator[i]=0.0;
        averagescore[i]=0.0;
        avgpayoff[i]=0.0;
    }

    

    for(int g=0; g<generations; g++){

        cout<<"running at: "<<g<<endl;

        for (int i=0; i<N; i++){

        x[i]=genomes[i][0];


        
        }
        
        float pi_c=0.0;

        float scores[N];

        for(int i=0; i<N; i++){
            scores[i]=0.0;
        }
    
        game(N, genomes, history, pi_c, scores);

        // for (int j=0; j<N; j++){
        //     cout<<scores[j]<<endl;
            

        // }

        float rands[N];

        for(int s=0; s<N; s++){

            rands[s]=distr(eng);


        }

        double avgscore=0.0;

        fitness(N, scores, genomes, rands, avgscore);

        averagescore[g]=avgscore;

        mutation(0.001, "Uniform", N, genomes);


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
        // cout<<inequal<<endl;
        selection[g]=N-inequal;
        evaluator[g]=p2[g]/(1-p1[g]+p2[g]);
        avgpayoff[g]=1-p2[g]+p_c[g]*(4-2*p1[g]+p2[g]);
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


    ofstream file4("selection.csv");

    if (file4.is_open()) {
        // Assuming you are writing some x and y data points
        for (int i = 0; i < generations; ++i) {
            double x2 = gencounter[i]; // your data for x
            double y2 = selection[i]; // example data for y, e.g., y = x^2
            file4 << x2 << "," << y2 << "\n";
        }
        file4.close();
    } else {
        cout << "Unable to open file";
    }

    ofstream file5("evaluator.csv");

    if (file5.is_open()) {
        // Assuming you are writing some x and y data points
        for (int i = 0; i < generations; ++i) {
            double x2 = gencounter[i]; // your data for x
            double y2 = evaluator[i]; // example data for y, e.g., y = x^2
            file5 << x2 << "," << y2 << "\n";
        }
        file5.close();
    } else {
        cout << "Unable to open file";
    }

    ofstream file6("averagescore.csv");

    if (file6.is_open()) {
        // Assuming you are writing some x and y data points
        for (int i = 0; i < generations; ++i) {
            double x2 = gencounter[i]; // your data for x
            double y2 = averagescore[i]; // example data for y, e.g., y = x^2
            file6 << x2 << "," << y2 << "\n";
        }
        file6.close();
    } else {
        cout << "Unable to open file";
    }


    ofstream file7("avgpayoff.csv");

    if (file7.is_open()) {
        // Assuming you are writing some x and y data points
        for (int i = 0; i < generations; ++i) {
            double x2 = gencounter[i]; // your data for x
            double y2 = avgpayoff[i]; // example data for y, e.g., y = x^2
            file7 << x2 << "," << y2 << "\n";
        }
        file7.close();
    } else {
        cout << "Unable to open file";
    }





    return 0;

}










