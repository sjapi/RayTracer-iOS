//
//  SceneDelegate.swift
//  RayTracerApp
//
//  Created by Arseniy Zolotarev on 16.07.2025.
//

import UIKit

class SceneDelegate: UIResponder, UIWindowSceneDelegate {
    
    var window: UIWindow?
    
    func scene(
        _ scene: UIScene,
        willConnectTo session: UISceneSession,
        options connectionOptions: UIScene.ConnectionOptions
    ) {
        guard let wc = (scene as? UIWindowScene) else { return }
        let vc = ViewController()
        window = UIWindow(windowScene: wc)
        window?.rootViewController = vc
        window?.overrideUserInterfaceStyle = .light
        window?.makeKeyAndVisible()
    }
}
