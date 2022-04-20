"""
Juego de la Vida 

- Martínez Ostoa Néstor Iván
- Sistemas Distribuidos
- UNAM
"""

import argparse
from ast import arg
from urllib.parse import ParseResult
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def initialize_grid(width, height):
    grid = np.random.randint(2, size=(width, height))
    return grid

def play(frame_number, img, grid):
    width, height = grid.shape
    x_dirs = [0,1,1,1,0,-1,-1,-1]
    y_dirs = [1,1,0,-1,-1,-1,0,1]
    
    new_grid = grid.copy()
    
    for y in range(height):
        for x in range(width):
            num_neighbors_on = 0
            cell = new_grid[y][x]
            
            for k in range(8):
                new_x = x + x_dirs[k]
                new_y = y + y_dirs[k]
                
                if (new_x < 0 or new_x >= width or new_y < 0 or new_y >= height):
                    continue
                    
                if new_grid[new_x][new_y] == 1: num_neighbors_on += 1
                    
            if cell == 1 and (num_neighbors_on < 2 or num_neighbors_on > 3):
                new_grid[y][x] = 0
                
            elif cell == 0 and num_neighbors_on == 3:
                new_grid[y][x] = 1
            
    img.set_data(new_grid)
    grid[:] = new_grid[:]
    return img,
    

def animate(grid):
    fig, ax = plt.subplots()
    img = ax.imshow(grid, interpolation='nearest')
    ani = FuncAnimation(
        fig, play, fargs=(img, grid,),
        frames = 100, interval=20, blit=True
    )

    w, h = grid.shape
    file_name = f'gol_{w}_{h}.gif'
    ani.save(f'./{file_name}', writer='imagemagick', fps=60)

    plt.show()

def main():
    width = 20
    height = 20

    parser = argparse.ArgumentParser()
    parser.add_argument('--width', dest='width', required=False)
    parser.add_argument('--height', dest='height', required=False)
    args = parser.parse_args()

    if args.width: width = int(args.width)
    if args.height: height = int(args.height)

    grid = initialize_grid(width, height)
    animate(grid)

if __name__ == '__main__':
    main()
