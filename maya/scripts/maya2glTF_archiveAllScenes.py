import maya
import zlib
import zipfile
import os as os
import maya.cmds as cmds
import maya.mel as mel

from os import path

def zipScenes(scenesDir=''):
    # get the default character encoding of the system
    theLocale = cmds.about(codeset=True)

    if (scenesDir == ''):

        currentScenePath = cmds.file(q=True, sn=True)

        if (currentScenePath == ''):
            cmds.error('Current scene has no filename! Please reload it.' )

        # get the folder of the current scene
        scenesDir = os.path.dirname(currentScenePath)

        if (scenesDir == ''):
            cmds.error('Cannot extract directory from current scene! Please reload it.' )

    # get all Maya scene files in that folder
    sceneFilenames = [f for f in os.listdir(scenesDir) if os.path.isfile(os.path.join(scenesDir, f)) and f.endswith('.ma')]   

    print (''.join(sceneFilenames))

    progressIndex = 0
    progressCount = len(sceneFilenames) * 2

    cmds.progressWindow(title='busy', min=0, max=progressCount, progress=0, status='initializing...', isInterruptable=True )

    try:

        zipPath = os.path.join(scenesDir, 'archive.zip')
        print('creating "%s"...' % zipPath)

        #if os.path.exists(zipPath):
        #    os.remove(zipPath)

        zip=zipfile.ZipFile(zipPath, 'w', zipfile.ZIP_DEFLATED)

        done=set()

        for sceneFilename in sceneFilenames:
            scenePath = os.path.join(scenesDir, sceneFilename)
            
            print('loading "%s"...' % scenePath)

            progressIndex += 1

            cmds.progressWindow(edit=True, progress=progressIndex, status='loading...' )

            # Check if the dialog has been cancelled
            if cmds.progressWindow( query=True, isCancelled=True ):
                cmds.error('cancelled')

            # open the file
            try:
                cmds.file( scenePath, o=True, iv=True, f=True, pmt=False)
            except:
                cmds.warning( 'errors occurred when loading %s!' % scenePath )    
                pass

            # Check if the dialog has been cancelled
            if cmds.progressWindow( query=True, isCancelled=True ):
                cmds.error('cancelled')

            progressIndex += 1

            cmds.progressWindow(edit=True, progress=progressIndex, status='zipping...' )

            # get a list of all the files associated with the scene
            files = cmds.file(query=1, list=1, withoutCopyNumber=1)

            # Check if the dialog has been cancelled
            if cmds.progressWindow( query=True, isCancelled=True ):
                cmds.error('cancelled')

            # workspacePath = cmds.workspace(q = True, fullName = True) + '/workspace.mel'    
            # files.append(workspacePath)
        
            # add each file associated with the scene, including the scene to the .zip file
            for file in files:
                # Check if the dialog has been cancelled
                if cmds.progressWindow( query=True, isCancelled=True ):
                    cmds.error('cancelled')

                if(path.isfile(file)):
                    name = file.encode(theLocale)
                    if (name in done):
                        print('already archived "%s", skipping' % file)
                    else:
                        print('archiving "%s"...' % file)
                        zip.write(name)
                        done.add(name)
                else:
                    cmds.warning( 'skipping %s' % file )

        # output a message whose result is the name of the zip file newly created
        print('"%s" created succesfully' % zipPath)
    except:
        print('failed to create "%s"!' % zipPath)
    finally:
        zip.close()
        cmds.progressWindow(endProgress=1)

#zipScenes()

