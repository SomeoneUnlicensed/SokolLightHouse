from PIL import Image, ImageDraw, ImageFont
import os

def generate_pinout():
    # Create a canvas
    width, height = 800, 600
    img = Image.new('RGB', (width, height), color=(255, 255, 255))
    draw = ImageDraw.Draw(img)
    
    # Draw Raspberry Pi 5 Header (Simplified)
    draw.rectangle([50, 50, 300, 550], outline="black", width=3)
    draw.text((70, 60), "Raspberry Pi 5 GPIO", fill="black")

    # Draw Neo-M8N GNSS
    draw.rectangle([500, 100, 750, 250], outline="blue", width=2)
    draw.text((520, 110), "u-blox Neo-M8N (GNSS)", fill="blue")

    # Draw SX1278 LoRa
    draw.rectangle([500, 350, 750, 500], outline="red", width=2)
    draw.text((520, 360), "Semtech SX1278 (LoRa)", fill="red")

    # Connections: GNSS (UART)
    # RPi Pin 8 (TX) -> GNSS RX, Pin 10 (RX) -> GNSS TX
    draw.line([300, 150, 500, 150], fill="blue", width=2) # TX-RX
    draw.text((320, 130), "UART TX -> RX", fill="blue")
    draw.line([300, 180, 500, 180], fill="blue", width=2) # RX-TX
    draw.text((320, 190), "UART RX <- TX", fill="blue")

    # Connections: LoRa (SPI)
    # SPI0: MOSI(19), MISO(21), SCLK(23), CE0(24)
    draw.line([300, 400, 500, 400], fill="red", width=2) # SPI
    draw.text((320, 410), "SPI (MOSI, MISO, SCK, CS)", fill="red")

    # Power
    draw.line([300, 100, 500, 100], fill="orange", width=2)
    draw.text((320, 80), "3.3V Power", fill="orange")
    draw.line([300, 500, 500, 500], fill="black", width=2)
    draw.text((320, 510), "GND", fill="black")

    # Save the image
    output_path = "SokolLightHouse/pinout_diagram.png"
    img.save(output_path)
    print(f"Diagram saved to {output_path}")

if __name__ == "__main__":
    generate_pinout()
