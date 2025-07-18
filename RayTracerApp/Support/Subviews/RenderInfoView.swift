//
//  RenderInfoView.swift
//  RayTracerApp
//
//  Created by Arseniy Zolotarev on 18.07.2025.
//

import UIKit

final class RenderInfoView: UIView {
    // MARK: UI Elements
    private let modeLabel: UILabel = UILabel()
    private let renderTimeLabel: UILabel = UILabel()
    
    // MARK: Init
    init(mode: Int32, renderTime: CLong) {
        super.init(frame: .zero)
        configureAppearance(mode, renderTime)
    }
    
    required init?(coder: NSCoder) {
        fatalError("storyboard sucks")
    }
    
    // MARK: Public Methods
    func update(_ mode: Int32, _ renderTime: CLong) {
        var modeStr: String
        switch mode {
        case RENDER_MODE:
            modeStr = "render"
        case CAMERA_MODE:
            modeStr = "camera"
        case OBJECT_MODE:
            modeStr = "object"
        case LIGHT_MODE:
            modeStr = "light"
        default:
            modeStr = "---"
        }
        modeLabel.text = "mode: \(modeStr)"
        let timeSeconds = Double(renderTime) / 1000.0
        renderTimeLabel.text = String(format: "%.3fs", timeSeconds)
    }
}

// MARK: Private Methods
private extension RenderInfoView {
    func configureAppearance(_ mode: Int32, _ renderTime: CLong) {
        frame.size = CGSize(width: UIScreen.main.bounds.width, height: 25)
        backgroundColor = .black
        modeLabel.textAlignment = .left
        renderTimeLabel.textAlignment = .right
        
        let padding: CGFloat = 12
        let labelWidth: CGFloat = frame.size.width / 2
        let labelHeight: CGFloat = 25
        modeLabel.frame.origin = CGPoint(
            x: padding,
            y: 0
        )
        renderTimeLabel.frame.origin = CGPoint(
            x: frame.width - padding - labelWidth,
            y: 0
        )
        [modeLabel, renderTimeLabel].forEach {
            $0.textColor = .systemGreen
            $0.font = .monospacedSystemFont(ofSize: 16, weight: .regular)
            $0.frame.size = CGSize(width: labelWidth, height: labelHeight)
            addSubview($0)
        }
        update(mode, renderTime)
    }
}
