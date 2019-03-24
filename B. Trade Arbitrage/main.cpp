#include<cmath>
#include<iostream>
#include<vector>
struct ArcGraph {
    explicit ArcGraph(int VCount);
    ~ArcGraph() = default;
    void AddEdge(int from, int to, double weight);
    int VCount() const;
    std::vector<double> GetVert(int i) const;
private:
    std::vector<std::vector<double>> NextVertices;
};

ArcGraph::ArcGraph(int VCount)                                  //делаем 0 вершин
{
    NextVertices.resize(0);
}

void ArcGraph::AddEdge(int from, int to, double weight)         //добавление ребра
{
    std::vector <double> new_pair(3);
    new_pair[0] = from;
    new_pair[1] = to;
    new_pair[2] = weight;
    NextVertices.push_back(new_pair);
}

int ArcGraph::VCount() const                            //число ребер
{
    return NextVertices.size();
}

std::vector<double> ArcGraph::GetVert(int i) const
{
    return NextVertices[i];
}

bool Belman_Ford(ArcGraph& graph, int N, double inf)                //пишем Белмана Форда
{
    std::vector<double>len(N, inf);                                 //расстояния
    len[0] = 0;
    for(int i = 0; i < N - 1; ++i)                                  //N - 1 раз делаем проход по всем ребрам
    {
        bool contin = false;
        for(int j = 0; j < graph.VCount(); ++j)                     //тут сам проход по ребру
        {
            std::vector<double>rebr = graph.GetVert(j);
            int from = rebr[0];
            int to = rebr[1];
            double weight = rebr[2];
            if(len[from] != inf && len[to] > len[from] + weight)
            {
                len[to] = len[from] + weight;               //если по этому ребру пройти дешевле то проходим
                contin = true;
            }
        }
        if(contin == false)
        {
            return false;
        }
    }
    for(int j = 0; j < graph.VCount(); ++j)                 //проходим ещё раз по всем ребрам
    {
        std::vector<double>rebr = graph.GetVert(j);
        int from = rebr[0];
        int to = rebr[1];
        double weight = rebr[2];
        if(len[from] != inf && len[to] > len[from] + weight)    //если можем пройти короче, то есть цикл отрицательной длины
        {
            return true;
        }
    }
    return false;
}

int main()
{
    double inf = 0;
    int N = 0;
    std::cin >> N;
    ArcGraph graph(N);
    for (int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(i != j)
            {
                double weight = 0;
                std::cin >> weight;
                if(weight != -1)
                {
                    graph.AddEdge(i, j, -log(weight));           //сведём задачу к нахождению отрицательного цикла
                    inf += abs(weight) + abs(log10(weight));
                }
            }
        }
    }
    if( Belman_Ford(graph, N, inf))
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }
}
