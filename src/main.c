// Main function
#include <stdio.h>
#include <stdlib.h>
#include "struct_list.h"


// Declarations of function prototypes
void calc_grid(struct block *grid_data, struct cell *cell_data);
void calc_fvm_coefficients(struct block *grid_data, struct coeff *fvm_coeff, struct properties *phys_prop);

// Main driver function
int main(void)
{
   int ii, jj, kk;

   // Define structs
   struct cell *cell_data;
   struct block *grid_data;
   struct coeff *fvm_coeff;
   struct properties *phys_prop;


   grid_data = (struct block *)malloc(sizeof(struct block));
   phys_prop = (struct properties *)malloc(sizeof(struct properties));

   // Enter inputs (replace with file parser later)
   grid_data->nx = 4;
   grid_data->ny = 3;
   grid_data->np = grid_data->nx*grid_data->ny;

   grid_data->xmin = 0.0;
   grid_data->xmax = 1.0;
   grid_data->ymin = 0.0;
   grid_data->ymax = 0.6;
   grid_data->dx = (grid_data->xmax-grid_data->xmin)/grid_data->nx;
   grid_data->dy = (grid_data->ymax-grid_data->ymin)/grid_data->ny;

   phys_prop->rho = 1.4;
   phys_prop->gamma = 0.6;
   phys_prop->u = 0.8;
   phys_prop->v = 0.8;

   phys_prop->Fx = phys_prop->rho*phys_prop->u;
   phys_prop->Fy = phys_prop->rho*phys_prop->v;
   phys_prop->Difx = phys_prop->gamma/grid_data->dx;
   phys_prop->Dify = phys_prop->gamma/grid_data->dy;
 
   phys_prop->Aw = grid_data->dy; 
   phys_prop->Ae = grid_data->dy; 
   phys_prop->As = grid_data->dx; 
   phys_prop->An = grid_data->dx; 

   // Allocate memory for 1D arrays of structs for cell and coefficient data structures
   cell_data = (struct cell *)malloc(grid_data->np * sizeof(struct cell));
   fvm_coeff = (struct coeff *)malloc(grid_data->np * sizeof(struct coeff));

   // Set cell centers
   calc_grid(grid_data, cell_data);



   // Test print statements

   // Print the cell centers
   printf("|  Cell Index  |  (x_cen, y_cen)  |\n");
   printf("|==============|==================|\n");
   for(ii = 0; ii < grid_data->np; ii++)
   {
      printf("      [%3i]       (%6.4f, %6.4f)\n",ii,cell_data[ii].x, cell_data[ii].y);
   }
//   calc_fvm_coefficients()

   calc_fvm_coefficients(grid_data, fvm_coeff, phys_prop);

   printf("|   a_W   |   a_E   |   a_S   |   a_N   |   S_u   |   S_p   |\n");
   printf("|=========|=========|=========|=========|=========|=========|\n");
   for(ii = 0; ii < grid_data->np; ii++)
   {
      printf("   %5.3f     %5.3f     %5.3f     %5.3f     %5.3f     %5.3f  \n",fvm_coeff[ii].a_W, fvm_coeff[ii].a_E, fvm_coeff[ii].a_S,fvm_coeff[ii].a_N,fvm_coeff[ii].S_u,fvm_coeff[ii].S_p);
   }
   return(0);
}
