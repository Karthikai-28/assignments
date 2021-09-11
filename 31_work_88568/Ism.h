#include <iostream>
#include <cmath>
#include <vector>

template <typename Key, typename Value>
struct keyComp {

    bool operator()(const std::pair<const Key, Value>& l, const std::pair<const Key, Value> r){
        return l.first < r.first;
    }
};

template <typename Key, typename Value, typename Comp = std::less<Key> >
class LSM 
{
public:

    LSM(const Comp& c = Comp());
    ~LSM();
    // If the Key is already present, update the value
    void insert(const std::pair<const Key,Value>& item); 
    // Return NULL if the Key doesn't exist in the map
    std::pair<const Key,Value>* find(const Key& key); 
    // Do nothing if the Key does not exist

    std::vector<std::vector<std::pair<const Key, Value> > > getmTree(){ return mTree;}
    void erase(const Key& key); 
    size_t size() const;
    bool empty() const;



    //print for debug
    void print();

private:
    size_t count;
    Comp c;
    std::vector<std::vector<std::pair<const Key, Value> > > mTree;

};

template <typename Key, typename Value, typename Comp>
LSM<Key, Value, Comp>::LSM(const Comp& c){
    this->c = c;
    count = 0; 
    std::vector<std::pair<const Key, Value> > emptyVector;
    mTree.push_back(emptyVector);
   
}

template <typename Key, typename Value, typename Comp>
LSM<Key, Value, Comp>::~LSM(){
    
}

template <typename Key, typename Value, typename Comp>
void LSM<Key, Value, Comp>::insert(const std::pair<const Key,Value>& item){

    if(find(item.first) != NULL)
    {
        find(item.first)->second = item.second;
        return;
    }

    if (mTree.empty()){
        count++;
        mTree[0].push_back(item);
        std::vector<std::pair<const Key, Value> > emptyVector;
        mTree.push_back(emptyVector);
        return;
    }

    int currLoc = 0;
    mTree[currLoc].push_back(item);
    while (1){

        
        if ((double)mTree[currLoc].size() == std::pow(2, currLoc)){
            count++;
            return;
        }
        //push to next index
        else{
            if (currLoc == mTree.size() - 1){
                std::vector<std::pair<const Key, Value> > emptyVector;
                mTree.push_back(emptyVector);
                mTree[currLoc+1].swap(mTree[currLoc]);
                mTree[currLoc].clear();
                count++;
                return;
            }
            else {
                for (unsigned int j = 0; j < mTree[currLoc].size(); j++){
                    mTree[currLoc+1].push_back(mTree[currLoc][j]);
                }
                mTree[currLoc].clear();
            }


        }

        currLoc++;
    }
}

template <typename Key, typename Value, typename Comp>
std::pair<const Key,Value>* LSM<Key, Value, Comp>::find(const Key& key){

    for (unsigned int i = 0; i < mTree.size(); i++){
        int l = 0;
        int r = mTree[i].size() - 1;
        while (l <= r){
            int m = (l+r)/2;
            if (mTree[i][m].first == key){
                return &(mTree[i][m]);
            }   
            else if (c(mTree[i][m].first, key)){
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }

    }
    return NULL;
}

template <typename Key, typename Value, typename Comp>
void LSM<Key, Value, Comp>::erase(const Key& key){


}

template <typename Key, typename Value, typename Comp>
size_t LSM<Key, Value, Comp>::size() const {

    return count;

}


template <typename Key, typename Value, typename Comp>
bool LSM<Key, Value, Comp>::empty() const {

    return (count == 0);
}

template <typename Key, typename Value, typename Comp>
void LSM<Key, Value, Comp>::print(){
    for (unsigned int i = 0; i < mTree.size(); i++){
        std::cout << "Index " << i << ": ";
        for (unsigned int j = 0; j < mTree[i].size(); j++){
            std::cout << mTree[i][j].first << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}