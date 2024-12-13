#include "Mesh.hxx"
#include <iostream>

//Constructor definition
Mesh::Mesh(int nx, int nvx, int nvy, int nvz, double domainLengthX, double domainMaxVX, double domainMaxVY, double domainMaxVZ, int bc) : 
            nx(nx), nvx(nvx), nvy(nvy), nvz(nvz), domainLengthX(domainLengthX), domainMaxVX(domainMaxVX), domainMaxVY(domainMaxVY), domainMaxVZ(domainMaxVZ), bc(bc)
{
    //Generate cells
    for (int i = 0; i < nx; i++) 
    {
        Cell cell;
        //Calculate length of each cell
        cell.dx = domainLengthX/nx; //Assuming cells are uniform length
        //Initialize vertices of the cell
        cell.vertices.push_back(i*cell.dx); //1D mesh
        cell.vertices.push_back((i+1)*cell.dx); 
        //Initialize neighbors of the cell
        if (i==0)
        {
            if (bc==0)
            {
                cell.neighbors.push_back(nx-1); //Periodic BC
            }
            else
            {
                cell.neighbors.push_back(nx); //Ghost cell left
            }
            cell.neighbors.push_back(i+1);
        }
        else if (i==nx-1)
        {
            cell.neighbors.push_back(i-1);
            if (bc==0)
            {
                cell.neighbors.push_back(0); //Periodic BC
            }
            else
            {
                cell.neighbors.push_back(nx+1); //Ghost cell right
            }
        }
        else
        {
            cell.neighbors.push_back(i - 1); 
            cell.neighbors.push_back(i + 1); 
        }

        cells.push_back(cell);
    }
    //Calculate velocity difference between discrete velocity points
    dvx = 2.0*domainMaxVX/(nvx-1.0); //Ensures velocity spans [-domainMaxVX, domainMaxVX]
    dvy = 2.0*domainMaxVY/(nvy-1.0);
    dvz = 2.0*domainMaxVZ/(nvz-1.0);
}

//Accessor function definition for cells
const std::vector<Cell>& Mesh::getCells() const 
{
    return cells;
}

//Return the number of cells in x
const int& Mesh::getNX() const
{
    return nx;
}

//Return the number of cells in x
const int& Mesh::getNVX() const
{
    return nvx;
}

const int& Mesh::getNVY() const
{
    return nvy;
}

const int& Mesh::getNVZ() const
{
    return nvz;
}

double Mesh::getDVX() const
{
    return dvx;
}

double Mesh::getDVY() const
{
    return dvy;
}

double Mesh::getDVZ() const
{
    return dvz;
}

double Mesh::getVelocityX(int velocityIndex) const
{
    return -domainMaxVX + velocityIndex*dvx;
}

double Mesh::getVelocityY(int velocityIndex) const
{
    return -domainMaxVY + velocityIndex*dvy;
}

double Mesh::getVelocityZ(int velocityIndex) const
{
    return -domainMaxVZ + velocityIndex*dvz;
}
