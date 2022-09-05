; ModuleID = './src/lib.c'
source_filename = "./src/lib.c"
target datalayout = "e-m:e-p:32:32-p10:8:8-p20:8:8-i64:64-n32:64-S128-ni:1:10:20"
target triple = "wasm32"

@arr = hidden global i32* null, align 4
@width = hidden global i32 0, align 4
@height = hidden global i32 0, align 4
@arr_len = hidden global i32 0, align 4

; Function Attrs: noinline nounwind optnone
define hidden void @acceptArray(i32* noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  %5 = alloca i32*, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  store i32* %0, i32** %5, align 4
  store i32 %1, i32* %6, align 4
  store i32 %2, i32* %7, align 4
  store i32 %3, i32* %8, align 4
  %10 = load i32*, i32** %5, align 4
  store i32* %10, i32** @arr, align 4
  %11 = load i32, i32* %6, align 4
  store i32 %11, i32* %9, align 4
  %12 = load i32, i32* %7, align 4
  store i32 %12, i32* @width, align 4
  %13 = load i32, i32* %8, align 4
  store i32 %13, i32* @height, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone
define hidden void @runGameAlgorithm() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  br label %4

4:                                                ; preds = %15, %0
  %5 = load i32, i32* %1, align 4
  %6 = load i32, i32* @arr_len, align 4
  %7 = icmp slt i32 %5, %6
  br i1 %7, label %8, label %18

8:                                                ; preds = %4
  %9 = load i32, i32* %1, align 4
  %10 = load i32, i32* @width, align 4
  %11 = srem i32 %9, %10
  store i32 %11, i32* %2, align 4
  %12 = load i32, i32* %1, align 4
  %13 = load i32, i32* @width, align 4
  %14 = sdiv i32 %12, %13
  store i32 %14, i32* %3, align 4
  br label %15

15:                                               ; preds = %8
  %16 = load i32, i32* %1, align 4
  %17 = add nsw i32 %16, 1
  store i32 %17, i32* %1, align 4
  br label %4, !llvm.loop !2

18:                                               ; preds = %4
  ret void
}

; Function Attrs: noinline nounwind optnone
define hidden i32 @getCell(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32*, i32** @arr, align 4
  %4 = load i32, i32* %2, align 4
  %5 = getelementptr inbounds i32, i32* %3, i32 %4
  %6 = load i32, i32* %5, align 4
  ret i32 %6
}

attributes #0 = { noinline nounwind optnone "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 14.0.0-1ubuntu1"}
!2 = distinct !{!2, !3}
!3 = !{!"llvm.loop.mustprogress"}
