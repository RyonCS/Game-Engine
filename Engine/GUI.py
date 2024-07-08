import tkinter as tk
from tkinter import filedialog

# This class represents our entire TileMap Editor program.
class TileMapEditor:
    def __init__(self, root):
        self.root = root
        self.root.title("Maze Maker")

        # Set the size and background color of the canvas
        self.canvas_width = 640
        self.canvas_height = 480
        self.canvas = tk.Canvas(root, width=self.canvas_width, height=self.canvas_height, bg="white")
        self.canvas.pack()

        # A tile size is 20 to match out .bmp game entity sizes.
        self.tile_size = 20
        # A dictionary to store tile types and x/y coordinates.
        self.tiles = {} 

        # Our options for tile types. green=grass. grey=rock. yellow=winner. blue=main character.
        self.tile_types = ["green", "grey", "yellow", "blue"]
        self.selected_tile_type = tk.StringVar()
        # Set the selected_tile_type to grass (default).
        self.selected_tile_type.set(self.tile_types[0])
        # Create drop down menu to select tile type.
        self.tile_menu = tk.OptionMenu(root, self.selected_tile_type, *self.tile_types)
        self.tile_menu.pack()

        # Allows the user to save their level to a .txt file.
        self.save_button = tk.Button(root, text="Save Level", command=self.save_level)
        self.save_button.pack()

        # Creates a toggle/buttom for delete-mode to delete tiles from the editor.
        self.delete_mode = False
        self.delete_button = tk.Button(root, text="Delete Tile", command=self.toggle_delete_mode)
        self.delete_button.pack()

        # Left-click becomes place tile when delete_mode is off.
        self.canvas.bind("<Button-1>", self.place_tile)

    # Places a tile on the tile editor screen and adds it to the dictionary of tiles.
    def place_tile(self, event):
        # Check if we're in delete mode. If not...
        if not self.delete_mode:
            # Get the x and y coordinates of where the tile is places.
            x = event.x // self.tile_size * self.tile_size
            y = event.y // self.tile_size * self.tile_size

            # Get the tile type that was selected.
            tile_type = self.selected_tile_type.get()
            tile_location = (x, y)

            # Change tile color to a type our program can understand.
            if tile_type == "green":
                tile_name = "grass"
            elif tile_type == "grey":
                tile_name = "rock"
            elif tile_type == "yellow":
                tile_name = "winner"
            elif tile_type == "blue":
                tile_name = "player"
            # Draw the tile to the screen.
            tile = self.canvas.create_rectangle(x, y, x + self.tile_size, y + self.tile_size, fill=tile_type)
            
            # Add tile to dictionary where key is tile position, tile is the object draw, and tile_name is the type of tile.
            self.tiles[tile_location] = (tile, tile_name)

    # Deletes a tile from the screen and our dictionary.
    def delete_tile(self, event):
        # Check if delete mode is on. If so...
        if self.delete_mode:
            # Get x/y coordinates of what was clicked on.
            x = self.canvas.canvasx(event.x)
            y = self.canvas.canvasy(event.y)

            x1 = x // self.tile_size * self.tile_size
            y1 = y // self.tile_size * self.tile_size

            # Generate key based on tile location.
            tile_location = (x1, y1)
            # Check if tile is in dictionary. If it is, delete the tile from the screen and dictionary.
            if tile_location in self.tiles:
                tile, name = self.tiles.pop(tile_location)
                self.canvas.delete(tile)

    # Toggls delete mode on and off.
    def toggle_delete_mode(self):
        self.delete_mode = not self.delete_mode
        # If delete mode on, left-click becomes delete tile.
        if self.delete_mode:
            self.delete_button.config(text="Delete On")
            self.canvas.bind("<Button-1>", self.delete_tile)
        # If delete mode off, left-click becomes add tile.
        else:
            self.delete_button.config(text="Delete Off")
            self.canvas.bind("<Button-1>", self.place_tile)

    # Allows the user to save the level to a file.
    def save_level(self):
        # Opens a dialogue file explorer menu so the user can choose where to save the file. Default is .txt.
        filename = filedialog.asksaveasfilename(defaultextension=".txt",
                                                  filetypes=[("Text files", "*.txt"), ("All files", "*.*")],
                                                  title="Save Level As")

        # Write the level to the file.
        with open(filename, "w") as file:
            for tile_id, tile_type in self.tiles.items():
                x, y = tile_id
                # Write the object type and x y coordinates to .txt file.
                file.write(f"{tile_type[1]} {x} {y} \n")


# Run our program.
if __name__ == "__main__":
    root = tk.Tk()
    app = TileMapEditor(root)
    root.mainloop()
