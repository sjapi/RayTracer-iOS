//
//  KeyButton.swift
//  RayTracerApp
//
//  Created by Arseniy Zolotarev on 18.07.2025.
//

import UIKit

final class KeyButton: UIButton {
    // MARK: Properties
    private var tapHandler: (() -> Void)?
    private let key: String
    let id: Int32
    
    // MARK: Init
    init(key: String, id: Int32, color: UIColor? = nil) {
        if key.count > 1 {
            self.key = String(key.first ?? "?")
        } else {
            self.key = key
        }
        self.id = id
        super.init(frame: .zero)
        frame.size = CGSize(width: 60, height: 60)
        setTitle(key, for: .normal)
        tag = Int(id)
        if let color {
            backgroundColor = color
            setTitleShadowColor(.black, for: .normal)
        } else {
            backgroundColor = .systemGray6
            setTitleShadowColor(.white, for: .normal)
        }
        layer.cornerRadius = 12
    }
    
    required init?(coder: NSCoder) {
        fatalError("storyboard sucks")
    }
    
    // MARK: - Public Methods
    func handleTap(_ handler: @escaping () -> Void) {
        tapHandler = handler
        addTarget(self, action: #selector(didTap), for: .touchUpInside)
    }
}

// MARK - Private Methods
private extension KeyButton {
    @objc func didTap() {
        print("handler works")
        tapHandler?()
    }
}
