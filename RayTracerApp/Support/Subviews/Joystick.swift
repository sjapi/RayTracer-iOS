//
//  Joystick.swift
//  RayTracerApp
//
//  Created by Arseniy Zolotarev on 18.07.2025.
//

import UIKit

final class Joystick: UIView {
    var onChange: ((CGVector) -> Void)?
    private var vector = CGVector(dx: 0, dy: 0)
    
    // MARK: UI Elements
    private let stick = UIView()
    
    // MARK: Init
    override init(frame: CGRect) {
        super.init(frame: frame)
        configureAppearance()
    }
    
    required init?(coder: NSCoder) {
        fatalError("storyboard sucks")
    }
    
    // MARK: Override Touch Methods
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
    }
    
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        guard let touch = touches.first else { return }
        let location = touch.location(in: self)
        let dx = location.x - bounds.midX
        let dy = location.y - bounds.midY
        let distance = sqrt(dx * dx + dy * dy)
        let maxDistance = bounds.width / 2 - stick.bounds.width / 4
        if distance <= maxDistance {
            stick.center = location
        } else {
            let angle = atan2(dy, dx)
            let x = bounds.midX + cos(angle) * maxDistance
            let y = bounds.midY + sin(angle) * maxDistance
            stick.center = CGPoint(x: x, y: y)
        }
        let vec = CGVector(dx: dx / maxDistance, dy: dy / maxDistance)
        let length = sqrt(vec.dx * vec.dx + vec.dy * vec.dy)
        if length > 0 {
            let normalizedVec = CGVector(dx: vec.dx / length, dy: vec.dy / length)
            onChange?(normalizedVec)
        } else {
            onChange?(CGVector.zero)
        }
    }
    
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        UIView.animate(withDuration: 0.2) {
            self.stick.center = CGPoint(x: self.bounds.midX, y: self.bounds.midY)
        }
        onChange?(.zero)
    }
}

// MARK: Private Methods
private extension Joystick {
    func configureAppearance() {
        frame.size = CGSize(width: 150, height: 150)
        backgroundColor = .systemGray6
        layer.cornerRadius = frame.height / 2
        
        stick.backgroundColor = .darkGray
        stick.frame.size = CGSize(width: frame.height / 2, height: frame.height / 2)
        stick.center = CGPoint(x: bounds.midX, y: bounds.midY)
        stick.layer.cornerRadius = stick.frame.height / 2
        addSubview(stick)
    }
}
