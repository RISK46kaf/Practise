#!/usr/bin/python2.7

import  os, sys, shutil
import gi
gi.require_version('Vips', '8.0')
from gi.repository import Vips
from multiprocessing import Pool, cpu_count
import zipfile
from lxml import etree

# sys.path.append(os.path.abspath("./myData.py"))

flagF = "-f" #set filename
flagS = "-s" #set scales count
flagT = "-t" #set tile size
flagO = "-o" #set output directory
flagZ = "-z" #zip result with name
flagX = "-x" #create xml mapping of cutted image

def startOfFile(filename,outputDir,xmlOutput):
    with open(outputDir + "/" + xmlOutput +".xml", 'w+') as f:
        f.write('<image filename=\"'+filename+'\">\n')
        f.close

def appendToFile(outputDir,xmlOutput,value,width,height,tile_amount_w,tile_amount_h):
    with open(outputDir + "/" + xmlOutput +".xml", "a") as f:
        f.write('\t<scale value=\"'+str(value)+'\" width=\"'+str(width)+'\" height=\"'+str(height)+'\" tile_amount_w=\"'+str(tile_amount_w)+'\" tile_amount_h=\"'+str(tile_amount_h)+'\"/>\n')
        f.close

def endOfFile(outputDir,xmlOutput):
    tmp = outputDir + "/" + xmlOutput
    with open(tmp+".xml", "a") as f:
        f.write('</image>')
        f.close

def imageScales(filename,i,scalesCount,tileSize,outputDir,xmlOutput):
    image = Vips.Image.new_from_file(filename)
    sc = 1.0/float(i)
    scaled_image = image.similarity(scale = sc)
    if i != 1:
        mask = Vips.Image.new_from_array([[-1, -1,  -1],
                                      [-1,  16, -1],
                                      [-1, -1,  -1]], scale = 8)
        scaled_image = scaled_image.conv(mask)


    tile_amount_w = scaled_image.width / (tileSize[0]) + 1
    tile_amount_h = scaled_image.height / (tileSize[1]) + 1

    # mdt = myData(filename, i, scaled_image.width, scaled_image.height, tile_amount_w, tile_amount_h)
    appendToFile(outputDir,xmlOutput,i,scaled_image.width,scaled_image.height,tile_amount_w,tile_amount_h)
    shift_x = 0
    shift_y = 0
    last_pixel_x = 0 #scaled_image.width - ((tile_amount_w-1) * tileSize[0])
    last_pixel_y = 0 #scaled_image.height - ((tile_amount_h-1) * tileSize[1])
    dirName = outputDir
    previewDir = dirName + "/Preview"
    dirName = dirName + "/" + str(i)
    if not os.path.exists(dirName):
        os.mkdir(dirName)
    if not os.path.exists(previewDir):
        os.mkdir(previewDir)
    path = previewDir + "/1_" + str(i) + ".png"
    for h in range(0,int(tile_amount_h)):
    #{
        last_pixel_y = int(tileSize[1])
        if h == (tile_amount_h-1):
            last_pixel_y = scaled_image.height - ((tile_amount_h-1) * int(tileSize[1]))
        for w in range(0,int(tile_amount_w)):
        #{
            last_pixel_x = int(tileSize[0])
            if w == (tile_amount_w-1):
                last_pixel_x = scaled_image.width - ((tile_amount_w-1) * int(tileSize[0]))

            if last_pixel_x <= 0 or last_pixel_y <= 0:
                shift_x+= int(tileSize[0])
                continue
            path1 = dirName+"/"+"y="+str(h)+"x="+str(w)+".png";
            if scaled_image.width <= (shift_x + last_pixel_x) and scaled_image.height > (shift_y + last_pixel_y):
                tile = scaled_image.extract_area(shift_x,shift_y,scaled_image.width - shift_x, last_pixel_y)
                tile.write_to_file(path1)
                del tile
            elif scaled_image.width > (shift_x + last_pixel_x) and scaled_image.height <= (shift_y + last_pixel_y):
                tile = scaled_image.extract_area(shift_x,shift_y,last_pixel_x, scaled_image.height - shift_y)
                tile.write_to_file(path1)
                del tile
            elif scaled_image.width <= (shift_x + last_pixel_x) and scaled_image.height <= (shift_y + last_pixel_y):
                tile = scaled_image.extract_area(shift_x,shift_y,scaled_image.width - shift_x, scaled_image.height - shift_y)
                tile.write_to_file(path1)
                del tile
            else:
                tile = scaled_image.extract_area(shift_x,shift_y,last_pixel_x, last_pixel_y)
                tile.write_to_file(path1)
                del tile
            shift_x+= int(tileSize[0])
        #}
        shift_y= shift_y + int(tileSize[1])
        shift_x = 0
    #}
    if i == scalesCount:
        scaled_image = scaled_image.write_to_file(path)
    del scaled_image
    # del image
    # image_mm.close()
    #}

def zipper(zipname, dir_to_zip):
    dir_to_zip_len = len(dir_to_zip.rstrip(os.sep)) + 1
    with zipfile.ZipFile(zipname, mode='w', compression=zipfile.ZIP_DEFLATED) as zf:
        for dirname, subdirs, files in os.walk(dir_to_zip):
            for filename in files:
                path = os.path.join(dirname, filename)
                entry = path[dir_to_zip_len:]
                zf.write(path, entry)

def imageCrutter(filename,tileSize,scalesCount,outputDir,zipInfo,xmlOutput):
    pool = Pool(processes = cpu_count() * 2 )
    for x in xrange(1, scalesCount+1):
        pool.apply_async(imageScales, args=(filename,x,scalesCount,tileSize,outputDir,xmlOutput))
    pool.close()
    pool.join()
    del pool
    

def main(): #{
    params = sys.argv
    filename = "auto.jpg"
    defaultScalesCount = 10
    scalesCount = defaultScalesCount
    tileSize = 256,256
    outputDir = filename.replace(".","_")
    zipInfo = [False,filename.replace(".","_") + ".zip"]
    xmlOutput = "image"

    if (flagF in params and params.index(flagF) + 1 < len(params)):
        filename = params[params.index(flagF) + 1]
        assert os.path.exists(filename), "file with filename next '-f' has no exists"
        outputDir = filename.replace(".","_")

    if (flagS in params and params.index(flagS) + 1 < len(params)):
        try:
            scalesCount = int(params[params.index(flagS) + 1])
        except ValueError:
            assert False,"scales count is not integer"
        assert scalesCount > 0, "scales count is not positive number"
    if (flagT in params and params.index(flagT) + 2 < len(params)):
        tileSize = int(params[params.index(flagT) + 1]) , int(params[params.index(flagT) + 2])
    if (flagO in params and params.index(flagO) + 1 < len(params)):
        outputDir = params[params.index(flagO) + 1]
        if outputDir.endswith("/"):
            outputDir = outputDir[:-1]
        if not os.path.exists(outputDir):
            os.mkdir(outputDir)
    if flagZ in params:
        if params.index(flagZ) + 1 < len(params):
            zipInfo = [True,(params[params.index(flagZ) + 1]).replace(".","_")]
        else:
            zipInfo[0] = True
    if (flagX in params and params.index(flagX) + 1 < len(params)):
        xmlOutput = [True,params[params.index(flagX) + 1]]

    if not os.path.exists(outputDir):
        os.mkdir(outputDir)
    startOfFile(filename,outputDir,xmlOutput)
    try:
        imageCrutter(filename,tileSize,scalesCount,outputDir,zipInfo,xmlOutput)


    except IOError:
        assert False, "IOError: filename next '-f' not an image file"

    endOfFile(outputDir,xmlOutput)
    if zipInfo[0]:
    	zipper(zipInfo[1]+".zip",outputDir)
#}

if ( __name__ == "__main__"): #{
    main()
#}

    