/* comment */
#pragma once

#include <config_features.h>

#include <premac.h>
#include <Cocoa/Cocoa.h>
#include <postmac.h>

class AquaSalFrame;

@interface CocoaThreadEnabler : NSObject
{
}
-(void)enableCocoaThreads:(id)param;
@end

// our very own application
@interface VCL_NSApplication : NSApplication
{
}
-(void)applicationDidFinishLaunching:(NSNotification*)pNotification;
-(void)sendEvent:(NSEvent*)pEvent;
-(void)sendSuperEvent:(NSEvent*)pEvent;
-(NSMenu*)applicationDockMenu:(NSApplication *)sender;
-(BOOL)application: (NSApplication*) app openFile: (NSString*)file;
-(void)application: (NSApplication*) app openFiles: (NSArray*)files;
-(BOOL)application: (NSApplication*) app printFile: (NSString*)file;
-(NSApplicationPrintReply)application: (NSApplication *) app printFiles:(NSArray *)files withSettings: (NSDictionary *)printSettings showPrintPanels:(BOOL)bShowPrintPanels;
-(NSApplicationTerminateReply)applicationShouldTerminate: (NSApplication *) app;
-(void)applicationWillTerminate: (NSNotification *) aNotification;
-(void)systemColorsChanged: (NSNotification*) pNotification;
-(void)screenParametersChanged: (NSNotification*) pNotification;
-(void)scrollbarVariantChanged: (NSNotification*) pNotification;
-(void)scrollbarSettingsChanged: (NSNotification*) pNotification;
-(void)addFallbackMenuItem: (NSMenuItem*)pNewItem;
-(void)removeFallbackMenuItem: (NSMenuItem*)pOldItem;
-(void)addDockMenuItem: (NSMenuItem*)pNewItem;
#if !HAVE_FEATURE_MACOSX_SANDBOX
-(void)applicationWillBecomeActive: (NSNotification *)pNotification;
-(void)applicationWillResignActive: (NSNotification *)pNotification;
#endif
-(BOOL)applicationShouldHandleReopen: (NSApplication*)pApp hasVisibleWindows: (BOOL)bWinVisible;
-(void)setDockIconClickHandler: (NSObject*)pHandler;
@end

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
