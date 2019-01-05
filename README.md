# geoIMS
  geoIMS is a state of the art low coast Internet Maps Server written from scratch using the most popular 
open source tools C, Motif, X-Windows, unixODBC, ImageMagick, apache, PHP.
It support ODBC which make it easy to use any RDBMS (DB2, MySQL, ORACLE, …)
It is written under IBM AIX, migrated and tuned to be used under RedHat Linux.
It runs under IBM AIX, RedHat Linux and almost all Linux Platforms.
It can be migrated to any Unix/Linux System. 

geoIMS is designed so that we keep attributes data inside a database and load the graphics data only to RAM, then access attribute data on request.
This makes it faster in data loading and can handle huge data (up to ram size).



What is geoIMS:

    • Complete design and Implementation of spatial data engine 
        ◦ Create database                  (DDL for tables and indexes)
        ◦ Spatial tables design            (DB info, layer, feature, coordinates, ..)
        ◦ Tabular tables design            (feature have tables with primary key) 
        ◦ Network Connectivity tables      (Node-Arc-Node model)

    • Basic Data structure & File formats
        ◦ Data structure for all elements  (layer, feature, xy-coordinates, …)
        ◦ Layer file format                (up to 255 layer) 
        ◦ Symbol file format               (convert 1000 symbol from geoGPG)
        ◦ Font File format                 (convert 24 font from goeGPG)
        ◦ Spatial ASCII file format
        ◦ Spatial Fast loading Binary file format	   

    • File Menu
        ◦ New                  
        ◦ Open database  
            ▪ Retrieve all database
            ▪ Area Retrieval
            ▪ Network Retrieval
        ◦ Save workspace data into database 
        ◦ Import/Export AutoCAD DXF 
        ◦ Import/Export Spatial ASCII file
        ◦ Import/Export Spatial Binary file
        ◦ Exit                  

    • View Menu
        ◦ Draw 
        ◦ Window
        ◦ Zoom in
        ◦ Zoom out
        ◦ Zoom all
        ◦ Pan
        ◦ Set scale

    • Feature Menu
        ◦ Add point feature
        ◦ Add line   feature
        ◦ Add text   feature   
        ◦ Edit feature attribute      
        ◦ Edit feature graphics
        ◦ Delete Feature
        ◦ Move Feature
        ◦ Split line feature
        ◦ Join line feature

    • Layer Dialogue 
        ◦ Display a dialogue for toggle on/off  workspace layer visibility

    • Plotting
        ◦ Create GL2 plot file from what is displayed on screen to fit the plot area 

    • MV Electric Network  
        ◦ Add Grid station
        ◦ Add Substation
        ◦ Add MV feeder
        ◦ Add Open point
        ◦ Build Connectivity on screen
        ◦ Full Network trace
        ◦ Trace Adjacent feature
        ◦ Open/Close Switch device  (open point)
        ◦ SLD Creation 

    • Street Network
        ◦ Add Node
        ◦ Add Arc
        ◦ Build Connectivity on screen
        ◦ Shortest Path ( supports directions and weights ) 

    • Miscellaneous GIS functions
        ◦ Distance
        ◦ Where xy ?
        ◦ Locate point
        ◦ Batch edge matching
        ◦ Map transfer (shift)
        ◦ Map scaling
        ◦ Raster image display (bitmap format only)
        ◦ Rubber pan while adding line features
        ◦ Rubber box while making a window on screen
        ◦ Change graphic cursor size
        ◦ Wait cursor while processing

    • geoINFO supported features
        ◦ Support up to 220 MB Graphic data (Maps)
        ◦ Supports up to 1,250,000 features
        ◦ Supports 21 different fonts
        ◦ Supports 20 different line types
        ◦ Supports 1000 symbols
        ◦ Parameter file supported

