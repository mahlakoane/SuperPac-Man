//Implement your Node struct here
#include<utility>
#include<cfloat>

typedef pair<int,int> Pair;
typedef pair<double,pair<int,int>> pair_value;

struct cell{
    Pair prev=make_pair(-1,-1);
    auto f=FLT_MAX, g=FLT_MAX, h=FLT_MAX;
    auto close = false;
};
