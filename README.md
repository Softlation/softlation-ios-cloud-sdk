# Softlation iOS SDK #

## TOC

- [Overview](#overview)
- [Working with the Library](#working-with-the-library)
  * [Installation via Pods](#installation-via-pods)
  * [Installation by copying libSoftlation Files](#installation-by-copying-libsoftlation-files)
- [Quickstart](#quickstart)
  * [Prerequisite](#prerequisite)
  * [Softlation Sync Integration](#softlation-sync-integration)
  * [Enabling QA Mode](#enabling-qa-mode-pro)
- [Licence](#licence-and-copyright)

## Overview ##

**Softlation**'s libSoftlation is a pre-compiled universal library that provides a simplest way to implement localisation updates and improve QA and a/b testing processes for your app using [**Softlation Service**](http://softlation.com). If you want use **Softlation Sync** and **Softlation QA** in your app you need to include the library in your app, please use Pods or download the latest **SoftlationSDK.dmg**, these zips contain pre-compiled universal library which support *armv7/armv7s/arm64/i386/x86_64* versions and can be used with iOS6+.

## Working with the Library ##

### Installation via Pods ###

* Create or open `Podfile` and add your dependencies:

```objc
pod 'Softlation', '~> 1.0'
```

* Run `$ pod install` in your project directory.

### Installation by copying libSoftlation Files ###

Download and unzip the latest version of libSoftlation. Copy the "SoftlationSDK" directory in your project:

```javascript
cp -r SoftlationSDK /YourProject/
```

In addition you'll need to include `Softlation.h` in your source files.

## Quickstart ##

### Prerequisite ###

Before getting started you must perform the steps outlined above.

### Softlation Sync Integration ###

To enable **Softlation Sync** notifications, you need to do simple following steps:

* Add the following import definitions to the `AppDelegate.m` file.

```objc
#import "Softlation.h"
```

* Add the following code to the `didFinishLaunchingWithOptions` function.

```objc
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // Your other application code.....

    // We've recommend to implement Softlation Library right before the end of the method.

    // Set YES to enable QA Mode. Default is NO 
    // Please read below how to enable QA Mode for all your controllers with NSLocalizedString
    [Softlation setQAMode:NO];
    
    // Optionally, you can specify custom Launch Image that will be presented right after system launch Image. 
    // The second variable holds existed Launch Image during Softlation Sync which make Sync process smooth.
    [Softlation setCustomLaunchImage:(nil) holdLaunchImageWhileLoading:YES];

    // Here you should set up your API KEY of the app on Softlation Service.
    [Softlation configureWithToken:@"API_KEY" completionHandler:nil];

    return YES;
}
```

* Configure `API_KEY` with the given Softlation' API Key

### Enabling QA Mode [PRO] ###

If you set `[Softlation setQAMode:YES];` in your application delegate to make **QA Mode** work you also need to implement additional methods to all your controllers with `NSLocalizedString`

* Add the following methods in all view controllers, that should update strings:

```objc
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    
    if (self) {

        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(handleTranslationUpdated:)
                                                     name:kSoftlationTranslationUpdatedNotification object:nil];
    }
    return self;
}
 
- (void)handleTranslationUpdated:(NSNotification *)notification {
    // Update view texts, for details see below
}
 
- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}
```

* Add new method to controllers

If you have a table in your controller simply modify the following method:

```objc
- (void)handleTranslationUpdated:(NSNotification *)notification {
    
    // This line you need only if your controller consist Table View with NSLocalizedString, 
    // Add it for all your Table View using their names
    // By default you can set it to tableView
    [self.TABLEVIEWNAME reloadData];
 
}
```

* If you want to update other `NSLocalizedString` outside Table Views you need to call `[self.view setNeedsLayout]` in `handleTranslationUpdated` and simply reset values in `viewWillLayoutSubviews`

```objc
- (void)handleTranslationUpdated:(NSNotification *)notification {

    [self.view setNeedsLayout];

}

- (void)viewWillLayoutSubviews {

    [super viewWillLayoutSubviews];

    self.label1.text = NSLocalizedString(@"StringNameKey", nil);
    self.label2.text = NSLocalizedString(@"StringName2Key", nil);
    
}
```

If you have subviews without storing references to them in `@properties` you should handle these cases separately, probably recreating such subviews to reset text.

## Licence and Copyright ##

**Softlation** © 2014-2016 All Rights Reserved

*Unauthorised copying or unauthorised use is a violation of applicable laws.*