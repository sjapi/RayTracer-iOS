//
//  ViewController.swift
//  RayTracerApp
//
//  Created by Arseniy Zolotarev on 16.07.2025.
//

import UIKit
import CoreMotion

final class ViewController: UIViewController {
    private let motionManager = CMMotionManager()
    
    private let bytesPerPixel: Int = 4
    private var bytesPerRow: Int = 0
    
    private var width: CGFloat = 0
    private var height: CGFloat = 0
    private var context: CGContext!
    private var pixelBuffer: UnsafeMutablePointer<UInt8>!
    private var image: UIImage!
    private var imageView: UIImageView!
    
    var rt: UnsafeMutablePointer<t_rt>!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .white
        width = view.bounds.width
        height = view.bounds.width * 0.7
        bytesPerRow = Int(width) * bytesPerPixel;
        context = configureCGContext()
        pixelBuffer = configurePixelBuffer(context: context)
        render()
        image = convertCGImageToUIImage(context)
        imageView = UIImageView(image: image)
        imageView.frame = CGRect(x: 0, y: 50, width: width, height: height)
        
        let y = 50 + height + 20
        createButton(title: "Q", id: Int(KEY_Q), x: 20, y: y)
        createButton(title: "W", id: Int(KEY_W), x: 80, y: y)
        createButton(title: "E", id: Int(KEY_E), x: 140, y: y)
        createButton(title: "A", id: Int(KEY_A), x: 20, y: y + 60)
        createButton(title: "S", id: Int(KEY_S), x: 80, y: y + 60)
        createButton(title: "D", id: Int(KEY_D), x: 140, y: y + 60)
        
        createButton(title: "H", id: Int(KEY_H), x: 20, y: y + 150)
        createButton(title: "J", id: Int(KEY_J), x: 80, y: y + 150)
        createButton(title: "K", id: Int(KEY_K), x: 140, y: y + 150)
        createButton(title: "L", id: Int(KEY_L), x: 200, y: y + 150)
        
        createButton(title: "R", id: Int(KEY_R), x: 20, y: y + 240)
        createButton(title: "C", id: Int(KEY_C), x: 80, y: y + 240)
        view.addSubview(imageView)
    }
}

private extension ViewController {
    func configureCGContext() -> CGContext {
        let context = CGContext(
            data: nil,
            width: Int(width),
            height: Int(height),
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
        return data.bindMemory(to: UInt8.self, capacity: Int(width * height) * bytesPerPixel)
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
                Int32(width),
                Int32(height),
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
    
    func createButton(title: String, id: Int, x: CGFloat, y: CGFloat) {
        let button = UIButton(type: .system)
        button.frame = CGRect(x: x, y: y, width: 50, height: 50)
        button.backgroundColor = .systemGray6
        button.setTitleColor(.black, for: .normal)
        button.layer.cornerRadius = 12
        button.setTitle(title, for: .normal)
        button.tag = id  // вот ID кнопки
        
        button.addTarget(self, action: #selector(buttonPressed(_:)), for: .touchUpInside)
        
        view.addSubview(button)
    }
    
    @objc func buttonPressed(_ sender: UIButton) {
        let key = sender.tag
        var render = false
        print(key)
        if handle_qweasd(Int32(key), rt) {
            render = true
        }
        if handle_hjkl(Int32(key), rt) {
            render = true
        }
        if handle_other_keys(Int32(key), rt) {
            render = true
        }
        if render {
            rerender(rt)
            
            image = convertCGImageToUIImage(context)
            imageView.image = image
        }
    }
}

