package emancias;

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

public class Emancias {

    public static void main(String[] args) {
        File arquivo = new File("src/emancias/sangue.jpg");
        try {
            BufferedImage amostra = ImageIO.read(arquivo);
            BufferedImage emancias = new BufferedImage(amostra.getWidth(), amostra.getHeight(), BufferedImage.TYPE_INT_RGB);

            Color destaque = new Color(0xFF, 150, 150);

            for (int linha = 0; linha < amostra.getWidth(); linha++) {
                for (int coluna = 0; coluna < amostra.getHeight(); coluna++) {
                    Color pixel = new Color(amostra.getRGB(linha, coluna));
                    if (pixel.getBlue() < 200) {
                        emancias.setRGB(linha, coluna, destaque.getRGB());
                    } else {
                        emancias.setRGB(linha, coluna, amostra.getRGB(linha, coluna));

                    }
                }

            }
            ImageIO.write(emancias, "jpg", new File("src/emancias/resultado.jpg"));
        } catch (IOException ex) {
            System.out.println("Não existe a imagem");
        }

    }
}
