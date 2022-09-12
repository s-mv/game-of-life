import { sassPlugin } from 'esbuild-sass-plugin'
import esbuild from 'esbuild'

esbuild.build({
  entryPoints: ['./src/main.js'],
  bundle: true,
  minify: true,
  sourcemap: false,
  outfile: './public/index.js',
  plugins: [sassPlugin()]
})