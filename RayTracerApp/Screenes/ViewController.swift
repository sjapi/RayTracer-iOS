//
//  ViewController.swift
//  RayTracerApp
//
//  Created by Arseniy Zolotarev on 16.07.2025.
//

import UIKit
import CoreMotion

final class ViewController: UIViewController {
    private var letsRerender: Bool = false {
        didSet {
            if letsRerender {
                rerender(rt)
                renderInfoView.update(Int32(rt.pointee.mode), rt.pointee.render_time)
                image = convertCGImageToUIImage(context)
                imageView.image = image
            }
        }
    }
    
    private let motionManager = CMMotionManager()
    
    private let bytesPerPixel: Int = 4
    private var bytesPerRow: Int = 0
    
    private var win_width: CGFloat = 0
    private var win_height: CGFloat = 0
    private var context: CGContext!
    private var pixelBuffer: UnsafeMutablePointer<UInt8>!
    
    private var renderInfoView: RenderInfoView!
    private var image: UIImage!
    private var imageView: UIImageView!
    
    var rt: UnsafeMutablePointer<t_rt>!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .white
        win_width = view.bounds.width
        win_height = view.bounds.width * 0.7
        bytesPerRow = Int(win_width) * bytesPerPixel;
        context = configureCGContext()
        pixelBuffer = configurePixelBuffer(context: context)
        render()
        image = convertCGImageToUIImage(context)
        imageView = UIImageView(image: image)
        imageView.frame = CGRect(x: 0, y: 50 + 25, width: win_width, height: win_height)
        view.addSubview(imageView)
        
        configureInfoView()
        createQWEASDControls()
        createOtherControls()
    }
}

private extension ViewController {
    func configureInfoView() {
        renderInfoView = RenderInfoView(mode: Int32(rt.pointee.mode), renderTime: rt.pointee.render_time)
        renderInfoView.frame.origin = CGPoint(x: 0, y: 50)
        view.addSubview(renderInfoView)
    }
    
    func configureCGContext() -> CGContext {
        let context = CGContext(
            data: nil,
            width: Int(win_width),
            height: Int(win_height),
            bitsPerComponent: 8,
            bytesPerRow: bytesPerRow,
            space: CGColorSpaceCreateDeviceRGB(),
            bitmapInfo: CGBitmapInfo(rawValue: CGImageAlphaInfo.premultipliedLast.rawValue)
                .union(.byteOrder32Big)
                .rawValue
        )
        if let context {
            return context
        } else {
            fatalError("Unable to create cg context")
        }
    }
    
    func configurePixelBuffer(context: CGContext) -> UnsafeMutablePointer<UInt8> {
        guard let data = context.data else {
            fatalError("Unable to get data from context")
        }
        return data.bindMemory(to: UInt8.self, capacity: Int(win_width * win_height) * bytesPerPixel)
    }
    
    func convertCGImageToUIImage(_ context: CGContext) -> UIImage {
        let cgImage = context.makeImage()
        guard let cgImage else {
            fatalError("Unable to make cg image from cg context")
        }
        return UIImage(cgImage: cgImage)
    }
    
    func printPixel(x: Int, y: Int) {
        let offset = (y * bytesPerRow) + (x * bytesPerPixel)
        print(pixelBuffer[offset])
    }
    
    func render() {
        guard let path = Bundle.main.path(forResource: "sp", ofType: "rt") else {
            fatalError("Cannot find scene file")
        }
        path.withCString { cString in
            let rtPtr = init_rt(
                UnsafeMutablePointer(mutating: cString),
                Int32(win_width),
                Int32(win_height),
                pixelBuffer,
                Int32(bytesPerPixel * 8),
                Int32(bytesPerRow)
            )
            if let rtPtr {
                rt = rtPtr
            } else {
                print("Failed to init rt")
            }
        }
    }
    
    func createQWEASDControls() {
        let qweasd: [KeyButton] = [
            KeyButton(key: "Q", id: KEY_Q),
            KeyButton(key: "W", id: KEY_W, color: .systemYellow),
            KeyButton(key: "E", id: KEY_E),
            KeyButton(key: "A", id: KEY_A, color: .systemPink),
            KeyButton(key: "S", id: KEY_S, color: .systemCyan),
            KeyButton(key: "D", id: KEY_D, color: .systemPurple),
        ]
        let inset = CGFloat(15)
        let origin = CGPoint(x: inset, y: 50 + win_width + inset)
        let side = CGFloat(60)
        for (i, button) in qweasd.enumerated() {
            button.handleTap { [weak self] in
                guard let self else { return }
                handle_qweasd(button.id, rt)
                letsRerender = true
            }
            button.frame.origin = CGPoint(
                x: origin.x + (side + inset) * CGFloat(Int(i % 3)),
                y: origin.y + (side + inset) * CGFloat(Int(i / 3))
            )
            view.addSubview(button)
        }
    }
    
    func createOtherControls() {
        let rc: [KeyButton] = [
            KeyButton(key: "R", id: KEY_R),
            KeyButton(key: "C", id: KEY_C),
        ]
        let inset = CGFloat(15)
        let origin = CGPoint(x: inset, y: 50 + win_width + inset + 160)
        let side = CGFloat(60)
        for (i, button) in rc.enumerated() {
            button.handleTap { [weak self] in
                guard let self else { return }
                handle_other_keys(button.id, rt)
                letsRerender = true
            }
            button.frame.origin = CGPoint(
                x: origin.x + (side + inset) * CGFloat(Int(i % 3)),
                y: origin.y + (side + inset) * CGFloat(Int(i / 3))
            )
            view.addSubview(button)
        }
    }
}

