//
//  Softlation.h
//  libSoftlation 1.0
//
//  Created by Softlation Team
//  Copyright (c) 2014-2016 Softlation. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifdef NSLocalizedString
#undef NSLocalizedString
#define NSLocalizedString(key, comment) [Softlation translationForKey:key]
#endif

extern NSString *const kSoftlationTranslationUpdatedNotification;

@interface Softlation : NSObject

+ (void)setQAMode:(BOOL)qa;
+ (void)setCustomLaunchImage:(NSString *)launchImage holdLaunchImageWhileLoading:(BOOL)hold;
+ (void)configureWithToken:(NSString *)token completionHandler:(void (^)(NSError *error))completionHandler;
+ (void)updateTranslationWithCompletionHandler:(void (^)(NSError *error))completionHandler;
+ (void)setLang:(NSString *)lang;
+ (void)setTag:(NSString *)tag;
+ (NSString *)translationForKey:(NSString *)key;
+ (void)loadAvailableLangsWithCompletionHandler:(void (^)(NSArray *langs, NSError *error))completionHandler;

@end