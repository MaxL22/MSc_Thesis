; Load the edge ID/offset for this BB from the guard array
%22 = load i32, ptr inttoptr (i64 add (i64 ptrtoint (ptr @__sancov_gen_ to i64), i64 28) to ptr), align 4, !dbg !96, !nosanitize !69
%23 = sext i32 %22 to i64, !dbg !96
; Calculate pointer to this edge's counter in the coverage map 
; (%0 is the map base pointer)
%24 = getelementptr i8, ptr %0, i64 %23, !dbg !96
; Load the current hit count
%25 = load i8, ptr %24, align 1, !dbg !96, !nosanitize !69
; Increment the hit count by 1
%26 = add i8 %25, 1, !dbg !96
; AFL++ "NeverZero" logic 
; If the counter wrapped around to 0, this forces it back to 1.
%27 = tail call i8 @llvm.umax.i8(i8 %26, i8 1), !dbg !96
; 6. Store the updated counter back to the coverage map
store i8 %27, ptr %24, align 1, !dbg !96, !nosanitize !69