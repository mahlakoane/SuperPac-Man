#ifndef MAZEENTITY_H
#define MAZEENTITY_H



///This has the role of capturing the common functionality of the maze
///objects read from files
class MazeEntity
{
    public:
        MazeEntity() {}
        virtual void ReadEntityFromFile()=0;
        ~MazeEntity() {}

    private:
};

#endif // MAZEENTITY_H
