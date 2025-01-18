Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  us/call  us/call  name    
 22.22      0.14     0.14                             rlVertex3f
 11.11      0.21     0.07                             glfwGetTime
  9.52      0.27     0.06                             GetGlyphIndex
  7.94      0.32     0.05                             ma_clip_samples_f32
  6.35      0.36     0.04                             DrawPixel
  6.35      0.40     0.04                             GetTime
  3.17      0.42     0.02                             DrawCircleSector
  3.17      0.44     0.02                             SwapScreenBuffer
  3.17      0.46     0.02                             rlNormal3f
  2.38      0.48     0.02                             _glfwPlatformGetTimerValue
  1.59      0.49     0.01      917    10.91    10.91  drawStars
  1.59      0.50     0.01                             DrawTextCodepoint
  1.59      0.51     0.01                             OnSendAudioDataToDevice
  1.59      0.52     0.01                             glfwGetClipboardString
  1.59      0.53     0.01                             ma_device_write_to_stream__pulse
  1.59      0.54     0.01                             ma_pcm_f32_to_s16
  1.59      0.55     0.01                             ma_pcm_f32_to_u8
  1.59      0.56     0.01                             makeContextCurrentGLX
  1.59      0.57     0.01                             rlClearScreenBuffers
  1.59      0.58     0.01                             rlColor3f
  1.59      0.59     0.01                             rlDrawRenderBatch
  1.59      0.60     0.01                             rlLoadRenderBatch
  1.59      0.61     0.01                             rlSetTexture
  1.59      0.62     0.01                             rlTexCoord2f
  0.79      0.62     0.01                             _glfwPlatformGetTimerFrequency
  0.79      0.63     0.01                             ma_mutex_lock__posix
  0.79      0.63     0.01                             ma_mutex_uninit__posix
  0.00      0.63     0.00   402994     0.00     0.00  getPointIsOnScreenScaled
  0.00      0.63     0.00   402994     0.00     0.00  removeCam
  0.00      0.63     0.00   103277     0.00     0.00  randSingle
  0.00      0.63     0.00    49794     0.00     0.00  applyCam
  0.00      0.63     0.00    49794     0.00     0.00  getRandomVector2OnScreen
  0.00      0.63     0.00     8926     0.00     0.00  drawCircle
  0.00      0.63     0.00     5961     0.00     0.00  enemyApplyVelocity
  0.00      0.63     0.00     5961     0.00     0.00  enemyGetTargetPosition
  0.00      0.63     0.00     5961     0.00     0.00  enemyNavigate
  0.00      0.63     0.00     5961     0.00     0.00  enemyShouldSpawnMissile
  0.00      0.63     0.00     5961     0.00     0.00  manageEnemy
  0.00      0.63     0.00     3784     0.00     0.00  enemyCanSeePlayer
  0.00      0.63     0.00     3668     0.00     0.00  randSingleFull
  0.00      0.63     0.00     3199     0.00     0.00  missileShouldBreak
  0.00      0.63     0.00     2198     0.00     0.00  min
  0.00      0.63     0.00     2198     0.00     0.00  navigateToPoint
  0.00      0.63     0.00     1834     0.00     0.00  randVec
  0.00      0.63     0.00     1799     0.00     0.00  positionInRangeOfBase
  0.00      0.63     0.00     1694     0.00     0.00  enemyShouldDieToMissile
  0.00      0.63     0.00      918     0.00     0.00  setBasePosition
  0.00      0.63     0.00      917     0.00     0.00  cameraShakeF
  0.00      0.63     0.00      917     0.00     0.00  drawBase
  0.00      0.63     0.00      917     0.00     0.00  drawBorder
  0.00      0.63     0.00      917     0.00     0.00  manageBase
  0.00      0.63     0.00      917     0.00     0.00  playerApplyVelocity
  0.00      0.63     0.00      917     0.00     0.00  refreshCamera
  0.00      0.63     0.00      883     0.00     0.00  refreshStars
  0.00      0.63     0.00      882     0.00     0.00  getInputVector
  0.00      0.63     0.00      882     0.00     0.00  handlePlayerMovment
  0.00      0.63     0.00      882     0.00     0.00  manageEnemies
  0.00      0.63     0.00      882     0.00     0.00  manageMissiles
  0.00      0.63     0.00      882     0.00     0.00  manageOrbs
  0.00      0.63     0.00      882     0.00     0.00  playerApplyAvoidanceForce
  0.00      0.63     0.00      882     0.00     0.00  playerApplyInputToVelocity
  0.00      0.63     0.00      882     0.00     0.00  playerGetAvoidanceForce
  0.00      0.63     0.00      214     0.00     0.00  getVectorTo
  0.00      0.63     0.00      214     0.00     0.00  manageMissileMovement
  0.00      0.63     0.00       35     0.00     0.00  buttonIsPressed
  0.00      0.63     0.00       35     0.00     0.00  drawButton
  0.00      0.63     0.00       35     0.00     0.00  positionInRect
  0.00      0.63     0.00       14     0.00     0.00  initEnemy
  0.00      0.63     0.00       14     0.00     0.00  spawnEnemyOnAvoidArea
  0.00      0.63     0.00        8     0.00     0.00  applyCameraShake
  0.00      0.63     0.00        6     0.00     0.00  fireMissile
  0.00      0.63     0.00        6     0.00     0.00  initMissile
  0.00      0.63     0.00        1     0.00     0.00  applyDamage
  0.00      0.63     0.00        1     0.00     0.00  destructStars
  0.00      0.63     0.00        1     0.00     0.00  initBase
  0.00      0.63     0.00        1     0.00     0.00  initStars

 %         the percentage of the total running time of the
time       program used by this function.

cumulative a running sum of the number of seconds accounted
 seconds   for by this function and those listed above it.

 self      the number of seconds accounted for by this
seconds    function alone.  This is the major sort for this
           listing.

calls      the number of times this function was invoked, if
           this function is profiled, else blank.

 self      the average number of milliseconds spent in this
ms/call    function per call, if this function is profiled,
	   else blank.

 total     the average number of milliseconds spent in this
ms/call    function and its descendents per call, if this
	   function is profiled, else blank.

name       the name of the function.  This is the minor sort
           for this listing. The index shows the location of
	   the function in the gprof listing. If the index is
	   in parenthesis it shows where it would appear in
	   the gprof listing if it were to be printed.

Copyright (C) 2012-2024 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.

		     Call graph (explanation follows)


granularity: each sample hit covers 2 byte(s) for 1.59% of 0.63 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]     22.2    0.14    0.00                 rlVertex3f [1]
-----------------------------------------------
                                                 <spontaneous>
[2]     11.1    0.07    0.00                 glfwGetTime [2]
-----------------------------------------------
                                                 <spontaneous>
[3]      9.5    0.06    0.00                 GetGlyphIndex [3]
-----------------------------------------------
                                                 <spontaneous>
[4]      7.9    0.05    0.00                 ma_clip_samples_f32 [4]
-----------------------------------------------
                                                 <spontaneous>
[5]      6.3    0.04    0.00                 DrawPixel [5]
-----------------------------------------------
                                                 <spontaneous>
[6]      6.3    0.04    0.00                 GetTime [6]
-----------------------------------------------
                                                 <spontaneous>
[7]      3.2    0.02    0.00                 DrawCircleSector [7]
-----------------------------------------------
                                                 <spontaneous>
[8]      3.2    0.02    0.00                 SwapScreenBuffer [8]
-----------------------------------------------
                                                 <spontaneous>
[9]      3.2    0.02    0.00                 rlNormal3f [9]
-----------------------------------------------
                                                 <spontaneous>
[10]     2.4    0.02    0.00                 _glfwPlatformGetTimerValue [10]
-----------------------------------------------
                0.01    0.00     917/917         main [18]
[11]     1.6    0.01    0.00     917         drawStars [11]
-----------------------------------------------
                                                 <spontaneous>
[12]     1.6    0.01    0.00                 DrawTextCodepoint [12]
-----------------------------------------------
                                                 <spontaneous>
[13]     1.6    0.01    0.00                 OnSendAudioDataToDevice [13]
-----------------------------------------------
                                                 <spontaneous>
[14]     1.6    0.01    0.00                 glfwGetClipboardString [14]
-----------------------------------------------
                                                 <spontaneous>
[15]     1.6    0.01    0.00                 ma_device_write_to_stream__pulse [15]
-----------------------------------------------
                                                 <spontaneous>
[16]     1.6    0.01    0.00                 ma_pcm_f32_to_s16 [16]
-----------------------------------------------
                                                 <spontaneous>
[17]     1.6    0.01    0.00                 ma_pcm_f32_to_u8 [17]
-----------------------------------------------
                                                 <spontaneous>
[18]     1.6    0.00    0.01                 main [18]
                0.01    0.00     917/917         drawStars [11]
                0.00    0.00    1834/8926        drawCircle [34]
                0.00    0.00     917/917         cameraShakeF [49]
                0.00    0.00     917/917         refreshCamera [54]
                0.00    0.00     917/917         playerApplyVelocity [53]
                0.00    0.00     917/917         drawBorder [51]
                0.00    0.00     917/917         manageBase [52]
                0.00    0.00     917/917         drawBase [50]
                0.00    0.00     883/883         refreshStars [55]
                0.00    0.00     882/882         handlePlayerMovment [57]
                0.00    0.00     882/882         manageMissiles [59]
                0.00    0.00     882/1799        positionInRangeOfBase [46]
                0.00    0.00     882/882         manageEnemies [58]
                0.00    0.00     882/882         manageOrbs [60]
                0.00    0.00      35/35          drawButton [67]
                0.00    0.00      35/35          buttonIsPressed [66]
                0.00    0.00      14/14          initEnemy [69]
                0.00    0.00      14/14          spawnEnemyOnAvoidArea [70]
                0.00    0.00       1/1           initStars [77]
                0.00    0.00       1/1           initBase [76]
                0.00    0.00       1/1           destructStars [75]
-----------------------------------------------
                                                 <spontaneous>
[19]     1.6    0.01    0.00                 makeContextCurrentGLX [19]
-----------------------------------------------
                                                 <spontaneous>
[20]     1.6    0.01    0.00                 rlClearScreenBuffers [20]
-----------------------------------------------
                                                 <spontaneous>
[21]     1.6    0.01    0.00                 rlColor3f [21]
-----------------------------------------------
                                                 <spontaneous>
[22]     1.6    0.01    0.00                 rlDrawRenderBatch [22]
-----------------------------------------------
                                                 <spontaneous>
[23]     1.6    0.01    0.00                 rlLoadRenderBatch [23]
-----------------------------------------------
                                                 <spontaneous>
[24]     1.6    0.01    0.00                 rlSetTexture [24]
-----------------------------------------------
                                                 <spontaneous>
[25]     1.6    0.01    0.00                 rlTexCoord2f [25]
-----------------------------------------------
                                                 <spontaneous>
[26]     0.8    0.01    0.00                 ma_mutex_lock__posix [26]
-----------------------------------------------
                                                 <spontaneous>
[27]     0.8    0.01    0.00                 ma_mutex_uninit__posix [27]
-----------------------------------------------
                                                 <spontaneous>
[28]     0.8    0.01    0.00                 _glfwPlatformGetTimerFrequency [28]
-----------------------------------------------
                0.00    0.00  402994/402994      refreshStars [55]
[29]     0.0    0.00    0.00  402994         getPointIsOnScreenScaled [29]
                0.00    0.00  402994/402994      removeCam [30]
-----------------------------------------------
                0.00    0.00  402994/402994      getPointIsOnScreenScaled [29]
[30]     0.0    0.00    0.00  402994         removeCam [30]
-----------------------------------------------
                0.00    0.00       1/103277      initBase [76]
                0.00    0.00       6/103277      manageEnemy [39]
                0.00    0.00      14/103277      initEnemy [69]
                0.00    0.00    3668/103277      randSingleFull [41]
                0.00    0.00   99588/103277      getRandomVector2OnScreen [33]
[31]     0.0    0.00    0.00  103277         randSingle [31]
-----------------------------------------------
                0.00    0.00   49794/49794       refreshStars [55]
[32]     0.0    0.00    0.00   49794         applyCam [32]
-----------------------------------------------
                0.00    0.00   49794/49794       refreshStars [55]
[33]     0.0    0.00    0.00   49794         getRandomVector2OnScreen [33]
                0.00    0.00   99588/103277      randSingle [31]
-----------------------------------------------
                0.00    0.00     214/8926        manageMissiles [59]
                0.00    0.00     917/8926        drawBase [50]
                0.00    0.00    1834/8926        main [18]
                0.00    0.00    5961/8926        manageEnemies [58]
[34]     0.0    0.00    0.00    8926         drawCircle [34]
-----------------------------------------------
                0.00    0.00    5961/5961        enemyNavigate [37]
[35]     0.0    0.00    0.00    5961         enemyApplyVelocity [35]
-----------------------------------------------
                0.00    0.00    5961/5961        enemyNavigate [37]
[36]     0.0    0.00    0.00    5961         enemyGetTargetPosition [36]
-----------------------------------------------
                0.00    0.00    5961/5961        manageEnemy [39]
[37]     0.0    0.00    0.00    5961         enemyNavigate [37]
                0.00    0.00    5961/5961        enemyGetTargetPosition [36]
                0.00    0.00    5961/5961        enemyApplyVelocity [35]
                0.00    0.00    3770/3784        enemyCanSeePlayer [40]
                0.00    0.00    2198/2198        navigateToPoint [44]
-----------------------------------------------
                0.00    0.00    5961/5961        manageEnemy [39]
[38]     0.0    0.00    0.00    5961         enemyShouldSpawnMissile [38]
-----------------------------------------------
                0.00    0.00    5961/5961        manageEnemies [58]
[39]     0.0    0.00    0.00    5961         manageEnemy [39]
                0.00    0.00    5961/5961        enemyShouldSpawnMissile [38]
                0.00    0.00    5961/5961        enemyNavigate [37]
                0.00    0.00       6/6           fireMissile [72]
                0.00    0.00       6/103277      randSingle [31]
-----------------------------------------------
                0.00    0.00      14/3784        initEnemy [69]
                0.00    0.00    3770/3784        enemyNavigate [37]
[40]     0.0    0.00    0.00    3784         enemyCanSeePlayer [40]
-----------------------------------------------
                0.00    0.00    3668/3668        randVec [45]
[41]     0.0    0.00    0.00    3668         randSingleFull [41]
                0.00    0.00    3668/103277      randSingle [31]
-----------------------------------------------
                0.00    0.00    3199/3199        manageMissileMovement [65]
[42]     0.0    0.00    0.00    3199         missileShouldBreak [42]
-----------------------------------------------
                0.00    0.00    2198/2198        navigateToPoint [44]
[43]     0.0    0.00    0.00    2198         min [43]
-----------------------------------------------
                0.00    0.00    2198/2198        enemyNavigate [37]
[44]     0.0    0.00    0.00    2198         navigateToPoint [44]
                0.00    0.00    2198/2198        min [43]
-----------------------------------------------
                0.00    0.00    1834/1834        cameraShakeF [49]
[45]     0.0    0.00    0.00    1834         randVec [45]
                0.00    0.00    3668/3668        randSingleFull [41]
-----------------------------------------------
                0.00    0.00     882/1799        main [18]
                0.00    0.00     917/1799        manageBase [52]
[46]     0.0    0.00    0.00    1799         positionInRangeOfBase [46]
-----------------------------------------------
                0.00    0.00    1694/1694        manageMissiles [59]
[47]     0.0    0.00    0.00    1694         enemyShouldDieToMissile [47]
-----------------------------------------------
                0.00    0.00       1/918         initBase [76]
                0.00    0.00     917/918         manageBase [52]
[48]     0.0    0.00    0.00     918         setBasePosition [48]
-----------------------------------------------
                0.00    0.00     917/917         main [18]
[49]     0.0    0.00    0.00     917         cameraShakeF [49]
                0.00    0.00    1834/1834        randVec [45]
-----------------------------------------------
                0.00    0.00     917/917         main [18]
[50]     0.0    0.00    0.00     917         drawBase [50]
                0.00    0.00     917/8926        drawCircle [34]
-----------------------------------------------
                0.00    0.00     917/917         main [18]
[51]     0.0    0.00    0.00     917         drawBorder [51]
-----------------------------------------------
                0.00    0.00     917/917         main [18]
[52]     0.0    0.00    0.00     917         manageBase [52]
                0.00    0.00     917/918         setBasePosition [48]
                0.00    0.00     917/1799        positionInRangeOfBase [46]
-----------------------------------------------
                0.00    0.00     917/917         main [18]
[53]     0.0    0.00    0.00     917         playerApplyVelocity [53]
-----------------------------------------------
                0.00    0.00     917/917         main [18]
[54]     0.0    0.00    0.00     917         refreshCamera [54]
-----------------------------------------------
                0.00    0.00     883/883         main [18]
[55]     0.0    0.00    0.00     883         refreshStars [55]
                0.00    0.00  402994/402994      getPointIsOnScreenScaled [29]
                0.00    0.00   49794/49794       getRandomVector2OnScreen [33]
                0.00    0.00   49794/49794       applyCam [32]
-----------------------------------------------
                0.00    0.00     882/882         playerApplyInputToVelocity [62]
[56]     0.0    0.00    0.00     882         getInputVector [56]
-----------------------------------------------
                0.00    0.00     882/882         main [18]
[57]     0.0    0.00    0.00     882         handlePlayerMovment [57]
                0.00    0.00     882/882         playerApplyInputToVelocity [62]
                0.00    0.00     882/882         playerApplyAvoidanceForce [61]
-----------------------------------------------
                0.00    0.00     882/882         main [18]
[58]     0.0    0.00    0.00     882         manageEnemies [58]
                0.00    0.00    5961/5961        manageEnemy [39]
                0.00    0.00    5961/8926        drawCircle [34]
-----------------------------------------------
                0.00    0.00     882/882         main [18]
[59]     0.0    0.00    0.00     882         manageMissiles [59]
                0.00    0.00    1694/1694        enemyShouldDieToMissile [47]
                0.00    0.00     214/214         manageMissileMovement [65]
                0.00    0.00     214/8926        drawCircle [34]
                0.00    0.00       7/8           applyCameraShake [71]
-----------------------------------------------
                0.00    0.00     882/882         main [18]
[60]     0.0    0.00    0.00     882         manageOrbs [60]
-----------------------------------------------
                0.00    0.00     882/882         handlePlayerMovment [57]
[61]     0.0    0.00    0.00     882         playerApplyAvoidanceForce [61]
                0.00    0.00     882/882         playerGetAvoidanceForce [63]
-----------------------------------------------
                0.00    0.00     882/882         handlePlayerMovment [57]
[62]     0.0    0.00    0.00     882         playerApplyInputToVelocity [62]
                0.00    0.00     882/882         getInputVector [56]
-----------------------------------------------
                0.00    0.00     882/882         playerApplyAvoidanceForce [61]
[63]     0.0    0.00    0.00     882         playerGetAvoidanceForce [63]
-----------------------------------------------
                0.00    0.00     214/214         manageMissileMovement [65]
[64]     0.0    0.00    0.00     214         getVectorTo [64]
-----------------------------------------------
                0.00    0.00     214/214         manageMissiles [59]
[65]     0.0    0.00    0.00     214         manageMissileMovement [65]
                0.00    0.00    3199/3199        missileShouldBreak [42]
                0.00    0.00     214/214         getVectorTo [64]
                0.00    0.00       1/1           applyDamage [74]
                0.00    0.00       1/8           applyCameraShake [71]
-----------------------------------------------
                0.00    0.00      35/35          main [18]
[66]     0.0    0.00    0.00      35         buttonIsPressed [66]
                0.00    0.00      35/35          positionInRect [68]
-----------------------------------------------
                0.00    0.00      35/35          main [18]
[67]     0.0    0.00    0.00      35         drawButton [67]
-----------------------------------------------
                0.00    0.00      35/35          buttonIsPressed [66]
[68]     0.0    0.00    0.00      35         positionInRect [68]
-----------------------------------------------
                0.00    0.00      14/14          main [18]
[69]     0.0    0.00    0.00      14         initEnemy [69]
                0.00    0.00      14/103277      randSingle [31]
                0.00    0.00      14/3784        enemyCanSeePlayer [40]
-----------------------------------------------
                0.00    0.00      14/14          main [18]
[70]     0.0    0.00    0.00      14         spawnEnemyOnAvoidArea [70]
-----------------------------------------------
                0.00    0.00       1/8           manageMissileMovement [65]
                0.00    0.00       7/8           manageMissiles [59]
[71]     0.0    0.00    0.00       8         applyCameraShake [71]
-----------------------------------------------
                0.00    0.00       6/6           manageEnemy [39]
[72]     0.0    0.00    0.00       6         fireMissile [72]
                0.00    0.00       6/6           initMissile [73]
-----------------------------------------------
                0.00    0.00       6/6           fireMissile [72]
[73]     0.0    0.00    0.00       6         initMissile [73]
-----------------------------------------------
                0.00    0.00       1/1           manageMissileMovement [65]
[74]     0.0    0.00    0.00       1         applyDamage [74]
-----------------------------------------------
                0.00    0.00       1/1           main [18]
[75]     0.0    0.00    0.00       1         destructStars [75]
-----------------------------------------------
                0.00    0.00       1/1           main [18]
[76]     0.0    0.00    0.00       1         initBase [76]
                0.00    0.00       1/103277      randSingle [31]
                0.00    0.00       1/918         setBasePosition [48]
-----------------------------------------------
                0.00    0.00       1/1           main [18]
[77]     0.0    0.00    0.00       1         initStars [77]
-----------------------------------------------

 This table describes the call tree of the program, and was sorted by
 the total amount of time spent in each function and its children.

 Each entry in this table consists of several lines.  The line with the
 index number at the left hand margin lists the current function.
 The lines above it list the functions that called this function,
 and the lines below it list the functions this one called.
 This line lists:
     index	A unique number given to each element of the table.
		Index numbers are sorted numerically.
		The index number is printed next to every function name so
		it is easier to look up where the function is in the table.

     % time	This is the percentage of the `total' time that was spent
		in this function and its children.  Note that due to
		different viewpoints, functions excluded by options, etc,
		these numbers will NOT add up to 100%.

     self	This is the total amount of time spent in this function.

     children	This is the total amount of time propagated into this
		function by its children.

     called	This is the number of times the function was called.
		If the function called itself recursively, the number
		only includes non-recursive calls, and is followed by
		a `+' and the number of recursive calls.

     name	The name of the current function.  The index number is
		printed after it.  If the function is a member of a
		cycle, the cycle number is printed between the
		function's name and the index number.


 For the function's parents, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the function into this parent.

     children	This is the amount of time that was propagated from
		the function's children into this parent.

     called	This is the number of times this parent called the
		function `/' the total number of times the function
		was called.  Recursive calls to the function are not
		included in the number after the `/'.

     name	This is the name of the parent.  The parent's index
		number is printed after it.  If the parent is a
		member of a cycle, the cycle number is printed between
		the name and the index number.

 If the parents of the function cannot be determined, the word
 `<spontaneous>' is printed in the `name' field, and all the other
 fields are blank.

 For the function's children, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the child into the function.

     children	This is the amount of time that was propagated from the
		child's children to the function.

     called	This is the number of times the function called
		this child `/' the total number of times the child
		was called.  Recursive calls by the child are not
		listed in the number after the `/'.

     name	This is the name of the child.  The child's index
		number is printed after it.  If the child is a
		member of a cycle, the cycle number is printed
		between the name and the index number.

 If there are any cycles (circles) in the call graph, there is an
 entry for the cycle-as-a-whole.  This entry shows who called the
 cycle (as parents) and the members of the cycle (as children.)
 The `+' recursive calls entry shows the number of function calls that
 were internal to the cycle, and the calls entry for each member shows,
 for that member, how many times it was called from other members of
 the cycle.

Copyright (C) 2012-2024 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.

Index by function name

   [7] DrawCircleSector       [72] fireMissile            [42] missileShouldBreak
   [5] DrawPixel              [56] getInputVector         [44] navigateToPoint
  [12] DrawTextCodepoint      [29] getPointIsOnScreenScaled [61] playerApplyAvoidanceForce
   [3] GetGlyphIndex          [33] getRandomVector2OnScreen [62] playerApplyInputToVelocity
   [6] GetTime                [64] getVectorTo            [53] playerApplyVelocity
  [13] OnSendAudioDataToDevice (raudio.c) [14] glfwGetClipboardString [63] playerGetAvoidanceForce
   [8] SwapScreenBuffer        [2] glfwGetTime            [46] positionInRangeOfBase
  [28] _glfwPlatformGetTimerFrequency [57] handlePlayerMovment [68] positionInRect
  [10] _glfwPlatformGetTimerValue [76] initBase           [31] randSingle
  [32] applyCam               [69] initEnemy              [41] randSingleFull
  [71] applyCameraShake       [73] initMissile            [45] randVec
  [74] applyDamage            [77] initStars              [54] refreshCamera
  [66] buttonIsPressed         [4] ma_clip_samples_f32    [55] refreshStars
  [49] cameraShakeF           [15] ma_device_write_to_stream__pulse (miniaudio.h) [30] removeCam
  [75] destructStars          [26] ma_mutex_lock__posix (miniaudio.h) [20] rlClearScreenBuffers
  [50] drawBase               [27] ma_mutex_uninit__posix (miniaudio.h) [21] rlColor3f
  [51] drawBorder             [16] ma_pcm_f32_to_s16      [22] rlDrawRenderBatch
  [67] drawButton             [17] ma_pcm_f32_to_u8       [23] rlLoadRenderBatch
  [34] drawCircle             [19] makeContextCurrentGLX (glx_context.c) [9] rlNormal3f
  [11] drawStars              [52] manageBase             [24] rlSetTexture
  [35] enemyApplyVelocity     [58] manageEnemies          [25] rlTexCoord2f
  [40] enemyCanSeePlayer      [39] manageEnemy             [1] rlVertex3f
  [36] enemyGetTargetPosition [65] manageMissileMovement  [48] setBasePosition
  [37] enemyNavigate          [59] manageMissiles         [70] spawnEnemyOnAvoidArea
  [47] enemyShouldDieToMissile [60] manageOrbs
  [38] enemyShouldSpawnMissile [43] min
