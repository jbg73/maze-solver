#ifndef MAZE_SOLVER_CELL_H
#define MAZE_SOLVER_CELL_H

#include <iostream>
#include <vector>
#include <globals.h>

/***********************************************************************
 * Cell object definition
 ***********************************************************************/ 
struct Cell{
    /**
     * @brief X coord
     */
    int x;
    /**
     * @brief Y coord
     */
    int y; 
    int local_dist;
    int global_dist;
    Cell* parent;
    /**
     * @brief vector of cell walls;
     * @details true if existing wall, false otherwise
     */
    bool walls[4];
    /**
     * @brief vector contained the directions that the cell has visited
     */
    std::vector<globals::DIRECTION> visited_neighbours;
    
    /**
     * @brief Construct a new Cell object
     */
    Cell() : x{0}, y{0}, local_dist{0}, global_dist{0}, walls{true,true,true,true}{}
    /**
     * @brief Construct a new Cell object
     * 
     * @param x_val X Coord
     * @param y_val Y Coord
     * @param walls_vals walls values
     */
    Cell(int x_val, int y_val, bool walls_vals[4]) : x{x_val}, y{y_val}{
        for(int i = 0; i < 4; i++){
            walls[i] = walls_vals[i];
        }
    }

    /**
     * @brief Checks whether the cell still has all walls
     * @details Is used when generating the maze. All cells begin with 4 walls. If it still ahs 4 walls, it hasn't 
     * visited all its neighbours.
     * 
     * @return true if has neighbours still to visit
     * @return false elsewhere
     */
    bool HasNonVisitedNeighbours() const;
    /**
     * @brief Checks whether the cell has a connection that has not yet been explored
     * @details A connection here means that there is no wall between the cells
     * 
     * @return true if non visited connection exists
     * @return false elsewhere
     */
    bool HasAvailableConnections() const;
    /**
     * @brief Checks wheter the neighbour in the specified direction has already been visited
     * 
     * @param dir direction in which to check if neighbour has been visited
     * @return true if neighbour has been visited
     * @return false elsewhere
     */
    bool IsDirectionVisited(globals::DIRECTION dir) const;
    /**
     * @brief Updates the list of visited neighbours based on the direction received.
     * @attention The direction stored is the opposite to the received, i.e. if moving globals::UP, next cell will have its globals::DOWN direction already visited
     * @param dir direction from which we arrive to the cell
     */
    void UpdateNextCellVisitedNeighbours(globals::DIRECTION dir);
    /**
     * @brief Get the Cell Edges 
     * @details As cells are displayed as squares, having all 4 edges coordinates is useful to draw the canvas
     * 
     * @return vector of pairs (X,Y) coordinates [TopLeft, TR, BottomRight, BL]
     */
    std::vector<std::pair<int,int>> GetCellEdges() const;
};

#endif