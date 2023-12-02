#include <fstream>

template<class LabelType>
Graph<LabelType>::Graph(){ }

template<class LabelType>
int getEdgeWeight(LabelType start, LabelType end) {

    std::fstream milesFile;
    milesFile.open("miles.txt");
    std::string temp;
    while(getline(milesFile, temp)) {
        if(temp.find(start) != std::string::npos) {
            if(temp.find(end) != std::string::npos) {

            std::string miles = temp.substr(temp.find(":") + 1);

            int weight = stoi(miles);
            return weight;
            }
        }
    }
    milesFile.close();
    return 0;

}
