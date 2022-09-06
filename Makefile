smv:
	@echo "-- Compiling C code to WASM. --"
	@mkdir -p src/.tmp
	@clang --target=wasm32 -emit-llvm -c -S ./src/lib.c -o ./src/.tmp/lib.ll
	@llc -march=wasm32 -filetype=obj ./src/.tmp/lib.ll
	@wasm-ld --no-entry --export-all -o ./src/.tmp/lib.wasm ./src/.tmp/lib.o
	@echo "------------ Done. ------------"
	@echo "-------------------------------"
	@echo "-------- Preparing UI. --------"
	@npm run build
	@echo "---------- All done! ----------"