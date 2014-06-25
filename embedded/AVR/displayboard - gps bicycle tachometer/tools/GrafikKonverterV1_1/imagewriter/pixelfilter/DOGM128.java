package imagewriter.pixelfilter;

import guicomponents.ColorPalette;

import java.io.IOException;

/**
 * Ein Pixelfilter, welcher die Umrechnung für DOGM/KS108 Displays vornimmt bei
 * welchen Das speicherlayout nicht linear zur Pixeldarstellung ist
 * 
 * @author Christoph Läubrich
 */
public class DOGM128 implements PixelFilter {

    public void filterBuffer(int width, int height, int[] pixelBuffer, Appendable bitBuffer, ColorPalette palette) throws IOException {
        if (height % 8 != 0) {
            throw new IOException("Die Höhe muß ein vielfaches von 8 sein, ist aber " + height + " Pixel");
        }

        for (int y = 0; y < height; y += 8) {
            for (int x = 0; x < width; x++) {
                for (int z = 7; z >= 0; z--) {
                    int pixelindex = (y + z) * width + x;
                    bitBuffer.append(palette.getColorEncoding(pixelBuffer[pixelindex]));
                }
            }
        }
    }

    public String getFilterName() {
        return "DOGM128/KS108 Filter";
    }

}
