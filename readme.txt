Some people have been asking for the finished Doom 3 megatexture code, so here it is. 

Things that still need to be done:
    ZLib compression.
    Multithreading.

I'm switching over to virtual texturing, so before I remove this code from my codebase, I'm simply archiving it.
This ONLY contains the files related to the Doom 3 MegaTexture implementation I finished. 

This will take some effort to get to compile in either vanilla or BFG(in branch I moved a lot of BFG code over to vanilla). but you will have an easier time putting this into the BFG edition.

This depot also contains the MegaGen tool I wrote that allows you to build megatextures pretty easily, but it does need work!

See the megaproject: dkbase/megagen/test_box.megagen 
