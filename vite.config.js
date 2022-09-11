import { defineConfig } from 'vite'

// https://vitejs.dev/config/
export default defineConfig({
  root: './src',
  base: '/game-of-life/',
  build: {
    outDir: '../',
    rollupOptions: {
      output: {
        entryFileNames: "public/[name].js",
        chunkFileNames: "public/[name].js",
        assetFileNames: "public/[name].[ext]"
      }
    }
  }
});