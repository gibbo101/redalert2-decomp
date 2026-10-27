// TechnoTypeClass::Read_INI (0x006DAF60)
// Reads the type's rules section (ini), then its art section (ArtINI,
// section Image=): image and cameo shapes, palette, weapon fire offsets.
// @ref ??0?$DynamicVectorClass@PAVBuildingTypeClass@@@@QAE@IPBQAVBuildingTypeClass@@@Z=0058e170
// @ref ??0?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@QAE@IPBQAVVoxelAnimTypeClass@@@Z=00653340
// @ref ??_C@_04BBDK@Size?$AA@=007d5e28
// @ref ??_C@_04DAEP@Dock?$AA@=007f7d78
// @ref ??_C@_04EMIP@Ammo?$AA@=007d1ba4
// @ref ??_C@_05DNPE@?$CFsFLH?$AA@=007f7318
// @ref ??_C@_05FNNK@Sight?$AA@=007f7b40
// @ref ??_C@_05HJMP@Naval?$AA@=007f7880
// @ref ??_C@_05LKKC@Cameo?$AA@=007f732c
// @ref ??_C@_05LKOI@Owner?$AA@=007f78b8
// @ref ??_C@_06CHPN@Gunner?$AA@=007f7888
// @ref ??_C@_06CPBB@Turret?$AA@=007f7d28
// @ref ??_C@_06EBJB@Weight?$AA@=007f7f98
// @ref ??_C@_06KIJA@Reload?$AA@=007f793c
// @ref ??_C@_06OBCK@Crewed?$AA@=007f7890
// @ref ??_C@_06PKIA@Points?$AA@=007f78cc
// @ref ??_C@_07BOEP@Storage?$AA@=007f7d98
// @ref ??_C@_07CENM@Primary?$AA@=007f7eb8
// @ref ??_C@_07CJBK@PipWrap?$AA@=007f7b70
// @ref ??_C@_07DIIK@JumpJet?$AA@=007f7610
// @ref ??_C@_07FIPD@Sensors?$AA@=007f7b84
// @ref ??_C@_07GMNO@Organic?$AA@=007f76d4
// @ref ??_C@_07JADG@Spawned?$AA@=007f7790
// @ref ??_C@_07KJJB@Nominal?$AA@=007f7be0
// @ref ??_C@_07LIOD@IsTrain?$AA@=007f807c
// @ref ??_C@_07NEFF@IFVMode?$AA@=007f79b4
// @ref ??_C@_07NNDI@Soylent?$AA@=007f79d8
// @ref ??_C@_07POH@VHPScan?$AA@=007f7f68
// @ref ??_C@_07PPNB@Crusher?$AA@=007d1b28
// @ref ??_C@_08CPI@Category?$AA@=007f7d80
// @ref ??_C@_08EEGD@NoShadow?$AA@=007f76b0
// @ref ??_C@_08FCMA@VoiceDie?$AA@=007f7e48
// @ref ??_C@_08FFAN@Warpable?$AA@=007f7714
// @ref ??_C@_08HBNM@RotCount?$AA@=007f7380
// @ref ??_C@_08IFIN@WalkRate?$AA@=007f80a0
// @ref ??_C@_08IFOG@Weapon?$CFd?$AA@=007f7ed0
// @ref ??_C@_08JAIB@AltCameo?$AA@=007f7320
// @ref ??_C@_08KDMB@IdleRate?$AA@=007f8094
// @ref ??_C@_08KKHD@PipScale?$AA@=007f7b78
// @ref ??_C@_08LAIG@Explodes?$AA@=007e8c20
// @ref ??_C@_08MACI@DieSound?$AA@=007f7cd4
// @ref ??_C@_09DAHP@MinDebris?$AA@=007f7f50
// @ref ??_C@_09DKMA@Invisible?$AA@=007f7868
// @ref ??_C@_09EDDM@SizeLimit?$AA@=007f7f7c
// @ref ??_C@_09EDMA@MoveSound?$AA@=007f7ce0
// @ref ??_C@_09FKGL@Remapable?$AA@=007f7374
// @ref ??_C@_09FMFK@VoiceMove?$AA@=007f7e80
// @ref ??_C@_09FPHJ@SpeedType?$AA@=007f80b8
// @ref ??_C@_09GKLM@AuxSound1?$AA@=007f7e2c
// @ref ??_C@_09HAOM@AutoCrush?$AA@=007f1a40
// @ref ??_C@_09HHHN@Explosion?$AA@=007d3850
// @ref ??_C@_09HICA@FireAngle?$AA@=007f7834
// @ref ??_C@_09HKEH@Crashable?$AA@=007f7604
// @ref ??_C@_09HPCM@MaxDebris?$AA@=007f7f5c
// @ref ??_C@_09JFAF@AuxSound2?$AA@=007f7e20
// @ref ??_C@_09JMHE@BombSight?$AA@=007f7ae8
// @ref ??_C@_09KBCF@Secondary?$AA@=007f7eac
// @ref ??_C@_09KHEO@RollAngle?$AA@=007f8024
// @ref ??_C@_09KPOE@Locomotor?$AA@=007f800c
// @ref ??_C@_09LMA@Cloakable?$AA@=007f7bd4
// @ref ??_C@_09NGKJ@ToProtect?$AA@=007f7800
// @ref ??_C@_09NKB@Trainable?$AA@=007f7898
// @ref ??_C@_09OBFO@CloakStop?$AA@=007f7da0
// @ref ??_C@_0BA@BJNB@DistributedFire?$AA@=007f7944
// @ref ??_C@_0BA@DMGG@SpawnReloadRate?$AA@=007f7744
// @ref ??_C@_0BA@GLFO@JumpjetTurnRate?$AA@=007f76a0
// @ref ??_C@_0BA@IMPA@ClearAllWeapons?$AA@=007f7edc
// @ref ??_C@_0BA@JPHL@ForbiddenHouses?$AA@=007f79e0
// @ref ??_C@_0BA@LPLK@OpportunityFire?$AA@=007f7954
// @ref ??_C@_0BA@MPOB@ReloadIncrement?$AA@=007f7920
// @ref ??_C@_0BA@PGHM@ImpactLandSound?$AA@=007ef6f0
// @ref ??_C@_0BB@BAIC@SecondaryFireFLH?$AA@=007f729c
// @ref ??_C@_0BB@CJNK@VeteranAbilities?$AA@=007f74b4
// @ref ??_C@_0BB@DEKJ@DeployFireWeapon?$AA@=007f797c
// @ref ??_C@_0BB@EAKM@CanPassiveAquire?$AA@=007f7a74
// @ref ??_C@_0BB@ECLL@ImpactWaterSound?$AA@=007ef700
// @ref ??_C@_0BB@ELOD@DamSmkOffScrnRel?$AA@=007f7c24
// @ref ??_C@_0BB@EOGD@GapRadiusInCells?$AA@=007f7bb0
// @ref ??_C@_0BB@GMFL@SBarrelThickness?$AA@=007f7278
// @ref ??_C@_0BB@HBEJ@BarrelHoldFrames?$AA@=007f7538
// @ref ??_C@_0BB@HFOF@JumpjetDeviation?$AA@=007f7618
// @ref ??_C@_0BB@HFOK@TurretHoldFrames?$AA@=007f7588
// @ref ??_C@_0BB@HGKA@LeadershipRating?$AA@=007f7ad4
// @ref ??_C@_0BB@HICE@SlowdownDistance?$AA@=007f7fcc
// @ref ??_C@_0BB@IFOJ@TiltsWhenCrushes?$AA@=007f7510
// @ref ??_C@_0BB@KGBA@JumpjetNoWobbles?$AA@=007f762c
// @ref ??_C@_0BB@MABP@AttackFriendlies?$AA@=007f75f0
// @ref ??_C@_0BB@OBM@PBarrelThickness?$AA@=007f72b0
// @ref ??_C@_0BB@PDHB@ImmuneToPsionics?$AA@=007f76f0
// @ref ??_C@_0BC@CNGM@DisguiseWhenStill?$AA@=007f7a88
// @ref ??_C@_0BC@CNML@ReselectIfLimboed?$AA@=007f7b2c
// @ref ??_C@_0BC@EPCP@HasTurretTooltips?$AA@=007f7f14
// @ref ??_C@_0BC@HEPP@DisableVoxelCache?$AA@=007f7348
// @ref ??_C@_0BC@KFKB@PreventAttackMove?$AA@=007f78d4
// @ref ??_C@_0BC@NKBB@CanApproachTarget?$AA@=007f7a50
// @ref ??_C@_0BC@OFCH@ImmuneToRadiation?$AA@=007f7798
// @ref ??_C@_0BC@OFFG@DamageSmokeOffset?$AA@=007f7c38
// @ref ??_C@_0BC@PEJB@?$CFsBarrelThickness?$AA@=007f72f4
// @ref ??_C@_0BC@PJOC@TurretRotateSound?$AA@=007f7d14
// @ref ??_C@_0BD@COHB@EliteSBarrelLength?$AA@=007f720c
// @ref ??_C@_0BD@GAAP@ConsideredAircraft?$AA@=007f76dc
// @ref ??_C@_0BD@HFED@DestroySmokeOffset?$AA@=007f7c10
// @ref ??_C@_0BD@HHCM@AccelerationFactor?$AA@=007f7fa0
// @ref ??_C@_0BD@HJOO@DefaultToGuardArea?$AA@=007f7720
// @ref ??_C@_0BD@HPIL@RefnSmokeOffsetTwo?$AA@=007f7be8
// @ref ??_C@_0BD@IDNF@RadialFireSegments?$AA@=007f7990
// @ref ??_C@_0BD@MAOK@AIBasePlanningSide?$AA@=007f78a4
// @ref ??_C@_0BD@NNMH@ElitePBarrelLength?$AA@=007f7250
// @ref ??_C@_0BD@OBGP@SpecialThreatValue?$AA@=007f73fc
// @ref ??_C@_0BD@OEAL@VoiceSpecialAttack?$AA@=007f7e54
// @ref ??_C@_0BD@OPGD@DisableShadowCache?$AA@=007f7334
// @ref ??_C@_0BD@PAKO@RefnSmokeOffsetOne?$AA@=007f7bfc
// @ref ??_C@_0BE@BHIF@LeaveTransportSound?$AA@=007f7cec
// @ref ??_C@_0BE@COAI@RejoinTeamIfLimboed?$AA@=007f7b18
// @ref ??_C@_0BE@DHDJ@DetectDisguiseRange?$AA@=007f7af4
// @ref ??_C@_0BE@FIGJ@BarrelRecoverFrames?$AA@=007f7524
// @ref ??_C@_0BE@HFPJ@ElitePrimaryFireFLH?$AA@=007f7264
// @ref ??_C@_0BE@LCEF@TurretRecoverFrames?$AA@=007f7574
// @ref ??_C@_0BE@PHDB@EnterTransportSound?$AA@=007f7d00
// @ref ??_C@_0BF@COME@SuppressionThreshold?$AA@=007f76bc
// @ref ??_C@_0BF@EHCD@TurretCompressFrames?$AA@=007f759c
// @ref ??_C@_0BF@HIFE@DeaccelerationFactor?$AA@=007f7fb4
// @ref ??_C@_0BF@MEFJ@PrerequisiteOverride?$AA@=007f7b48
// @ref ??_C@_0BF@NGMJ@BarrelCompressFrames?$AA@=007f754c
// @ref ??_C@_0BG@BHCO@EliteSBarrelThickness?$AA@=007f71f4
// @ref ??_C@_0BG@BIOE@SuperGapRadiusInCells?$AA@=007f7b98
// @ref ??_C@_0BG@CICI@NaturalParticleSystem?$AA@=007f7c94
// @ref ??_C@_0BG@GLPH@EliteSecondaryFireFLH?$AA@=007f7220
// @ref ??_C@_0BG@GPOD@IsSelectableCombatant?$AA@=007f73e4
// @ref ??_C@_0BG@HFGJ@ElitePBarrelThickness?$AA@=007f7238
// @ref ??_C@_0BG@NDFL@DamageParticleSystems?$AA@=007f7c64
// @ref ??_C@_0BH@IHKL@DestroyParticleSystems?$AA@=007f7c4c
// @ref ??_C@_0BH@LFA@DamageReducesReadiness?$AA@=007f7908
// @ref ??_C@_0BI@DNEJ@CanRecalcApproachTarget?$AA@=007f7a38
// @ref ??_C@_0BI@INLB@NaturalParticleLocation?$AA@=007f7c7c
// @ref ??_C@_0BJ@BMBB@AttackCursorOnFriendlies?$AA@=007f75d4
// @ref ??_C@_0BJ@CJDM@RequiresStolenSovietTech?$AA@=007f7a1c
// @ref ??_C@_0BJ@NNNB@RequiresStolenAlliedTech?$AA@=007f7a00
// @ref ??_C@_0BK@BMBP@TurretNotExportedOnGround?$AA@=007f71d8
// @ref ??_C@_0BK@FKPM@TargetStrengthCoefficient?$AA@=007f742c
// @ref ??_C@_0BK@IEP@DeathWeaponDamageModifier?$AA@=007f8048
// @ref ??_C@_0BK@NFLG@TargetDistanceCoefficient?$AA@=007f7410
// @ref ??_C@_0BL@INNB@MyEffectivenessCoefficient?$AA@=007f7488
// @ref ??_C@_0BL@OLCL@ThreatAvoidanceCoefficient?$AA@=007f7fe0
// @ref ??_C@_0BM@CHLC@AllowedToStartInMultiplayer?$AA@=007f77d4
// @ref ??_C@_0BN@CCKJ@ReadinessReductionMultiplier?$AA@=007f78e8
// @ref ??_C@_0BP@IODG@TargetSpecialThreatCoefficient?$AA@=007f7448
// @ref ??_C@_0BP@MMII@TargetEffectivenessCoefficient?$AA@=007f7468
// @ref ??_C@_0EI@LFNF@You?5have?5violated?5the?5limit?5of?5h@=007f739c
// @ref ??_C@_0L@CHH@VoiceEnter?$AA@=007f7dbc
// @ref ??_C@_0L@CNML@PitchSpeed?$AA@=007f8018
// @ref ??_C@_0L@DCNK@Teleporter?$AA@=007f7b8c
// @ref ??_C@_0L@DNPE@DeployTime?$AA@=007f7828
// @ref ??_C@_0L@DPKL@Passengers?$AA@=007d1b98
// @ref ??_C@_0L@EAKF@MobileFire?$AA@=007f7964
// @ref ??_C@_0L@GCMN@PitchAngle?$AA@=007f8030
// @ref ??_C@_0L@JMIA@NoAutoFire?$AA@=007f7840
// @ref ??_C@_0L@JMNJ@DeployFire?$AA@=007f7970
// @ref ??_C@_0L@KCOL@Repairable?$AA@=007f7874
// @ref ??_C@_0L@KGGK@GuardRange?$AA@=007f8064
// @ref ??_C@_0L@LCAL@StupidHunt?$AA@=007f77c8
// @ref ??_C@_0L@LKBN@Underwater?$AA@=007f7784
// @ref ??_C@_0L@NHOA@IsDropship?$AA@=007f803c
// @ref ??_C@_0L@NNNE@TypeImmune?$AA@=007f80ac
// @ref ??_C@_0L@PDBI@BuildLimit?$AA@=007f7d8c
// @ref ??_C@_0M@BIIO@ThreatPosed?$AA@=007f78c0
// @ref ??_C@_0M@BKME@EmptyReload?$AA@=007f7930
// @ref ??_C@_0M@BODL@VoiceSelect?$AA@=007f7e74
// @ref ??_C@_0M@CEPI@Accelerates?$AA@=007f7504
// @ref ??_C@_0M@CFLM@VisibleLoad?$AA@=007f7368
// @ref ??_C@_0M@DAGH@DoubleOwned?$AA@=007f8070
// @ref ??_C@_0M@DIAD@HoverAttack?$AA@=007f7f70
// @ref ??_C@_0M@DKHF@DeathWeapon?$AA@=007efd30
// @ref ??_C@_0M@EIOB@InitialAmmo?$AA@=007f79bc
// @ref ??_C@_0M@EMOA@ZFudgeCliff?$AA@=007f74f8
// @ref ??_C@_0M@ENDA@FlightLevel?$AA@=007f1100
// @ref ??_C@_0M@FCMP@VoiceAttack?$AA@=007f7e68
// @ref ??_C@_0M@GHNF@DebrisAnims?$AA@=007f7f28
// @ref ??_C@_0M@HOF@WeaponCount?$AA@=007f7efc
// @ref ??_C@_0M@IMCD@DeploySound?$AA@=007f7cc8
// @ref ??_C@_0M@LCEP@DamageSound?$AA@=007f7e08
// @ref ??_C@_0M@LMDC@DebrisTypes?$AA@=007f7f44
// @ref ??_C@_0M@MDCH@CreateSound?$AA@=007f7e14
// @ref ??_C@_0M@MDJD@TurretCount?$AA@=007f7f08
// @ref ??_C@_0M@MEPC@ShadowIndex?$AA@=007f735c
// @ref ??_C@_0M@MKBK@SelfHealing?$AA@=007f784c
// @ref ??_C@_0M@MLPM@CanDisguise?$AA@=007f7abc
// @ref ??_C@_0M@ODGK@DeploysInto?$AA@=007f7d6c
// @ref ??_C@_0M@ODMB@TargetLaser?$AA@=007f77bc
// @ref ??_C@_0M@OFPK@DestroyAnim?$AA@=007f7cac
// @ref ??_C@_0M@OHBF@RevealToAll?$AA@=007f7ac8
// @ref ??_C@_0M@OIKJ@TurretSpins?$AA@=007f7d30
// @ref ??_C@_0M@PANJ@Disableable?$AA@=007f780c
// @ref ??_C@_0N@BBAP@JumpjetCrash?$AA@=007f7670
// @ref ??_C@_0N@BCOO@LightningRod?$AA@=007f7d4c
// @ref ??_C@_0N@BFFM@Parasiteable?$AA@=007f7704
// @ref ??_C@_0N@BLBP@TurretTravel?$AA@=007f75b4
// @ref ??_C@_0N@CFDA@VoiceFalling?$AA@=007f7de8
// @ref ??_C@_0N@CIE@MissileSpawn?$AA@=007f7734
// @ref ??_C@_0N@DCBB@JumpjetAccel?$AA@=007f7650
// @ref ??_C@_0N@DGPM@BarrelTravel?$AA@=007f7564
// @ref ??_C@_0N@ECOD@TurretRecoil?$AA@=007f75c4
// @ref ??_C@_0N@ENMM@GapGenerator?$AA@=007f7bc4
// @ref ??_C@_0N@EPFM@VoiceSinking?$AA@=007f7dc8
// @ref ??_C@_0N@FFLN@BalloonHover?$AA@=007f7774
// @ref ??_C@_0N@FOMO@SensorsSight?$AA@=007f7b08
// @ref ??_C@_0N@GEFE@VoiceCapture?$AA@=007f7dac
// @ref ??_C@_0N@GJJP@PhysicalSize?$AA@=007f7f88
// @ref ??_C@_0N@HMBF@HunterSeeker?$AA@=007f77ac
// @ref ??_C@_0N@IIHD@JumpjetClimb?$AA@=007f7680
// @ref ??_C@_0N@IJKM@SinkingSound?$AA@=007ef6e0
// @ref ??_C@_0N@IOEE@ZFudgeTunnel?$AA@=007f74d8
// @ref ??_C@_0N@JCCJ@ZFudgeColumn?$AA@=007f74e8
// @ref ??_C@_0N@JM@RadarVisible?$AA@=007f7858
// @ref ??_C@_0N@KOBB@Prerequisite?$AA@=007f7b60
// @ref ??_C@_0N@LNIM@MovementZone?$AA@=007f71c8
// @ref ??_C@_0N@MDLC@TiberiumHeal?$AA@=007f14c8
// @ref ??_C@_0N@MFDE@SpawnsNumber?$AA@=007f7754
// @ref ??_C@_0N@MNAG@TurretOffset?$AA@=007f738c
// @ref ??_C@_0N@NECA@ZFudgeBridge?$AA@=007f74c8
// @ref ??_C@_0N@NHOB@MoveToShroud?$AA@=007f8084
// @ref ??_C@_0N@OBDC@ElitePrimary?$AA@=007f7e9c
// @ref ??_C@_0N@OCHO@ManualReload?$AA@=007f7d3c
// @ref ??_C@_0N@OLOK@CanRetaliate?$AA@=007f7a64
// @ref ??_C@_0N@PCBG@JumpjetSpeed?$AA@=007f7690
// @ref ??_C@_0O@CPDF@UndeploysInto?$AA@=007f7d5c
// @ref ??_C@_0O@DAME@AirRangeBonus?$AA@=007f79a4
// @ref ??_C@_0O@DEMB@VoiceFeedback?$AA@=007f7e38
// @ref ??_C@_0O@EAHM@UndeploySound?$AA@=007f7cb8
// @ref ??_C@_0O@ECCD@EliteWeapon?$CFd?$AA@=007f7ec0
// @ref ??_C@_0O@GIEP@SBarrelLength?$AA@=007f728c
// @ref ??_C@_0O@IABC@ImmuneToVeins?$AA@=007f77f0
// @ref ??_C@_0O@IICM@UndeployDelay?$AA@=007f7818
// @ref ??_C@_0O@IPFA@ChronoInSound?$AA@=007ef6d0
// @ref ??_C@_0O@JEMD@PermaDisguise?$AA@=007f7aac
// @ref ??_C@_0O@JLPJ@PBarrelLength?$AA@=007f72c4
// @ref ??_C@_0O@KIOL@CloakingSpeed?$AA@=007f7ffc
// @ref ??_C@_0O@LPPJ@VoiceCrashing?$AA@=007f7dd8
// @ref ??_C@_0O@NBIA@CrashingSound?$AA@=007f7df8
// @ref ??_C@_0O@NGKL@LandTargeting?$AA@=007f80d4
// @ref ??_C@_0O@PCPD@JumpjetHeight?$AA@=007f7660
// @ref ??_C@_0P@BBAA@DetectDisguise?$AA@=007f7a9c
// @ref ??_C@_0P@DGDG@UnloadingClass?$AA@=007f79c8
// @ref ??_C@_0P@EEJC@RequiredHouses?$AA@=007f79f0
// @ref ??_C@_0P@GHDN@DebrisMaximums?$AA@=007f7f34
// @ref ??_C@_0P@GOML@?$CFsBarrelLength?$AA@=007f7308
// @ref ??_C@_0P@IJHB@IsChargeTurret?$AA@=007f7eec
// @ref ??_C@_0P@JJIJ@ChronoOutSound?$AA@=007ef6c0
// @ref ??_C@_0P@KBOC@EliteSecondary?$AA@=007f7e8c
// @ref ??_C@_0P@LHED@JumpjetWobbles?$AA@=007f7640
// @ref ??_C@_0P@MBFL@EliteAbilities?$AA@=007f74a4
// @ref ??_C@_0P@MCMK@?$CFsTurretLocked?$AA@=007f72e4
// @ref ??_C@_0P@NDGK@NavalTargeting?$AA@=007f80c4
// @ref ??_C@_0P@PDLP@PrimaryFireFLH?$AA@=007f72d4
// @ref ??_C@_0P@PNDO@SpawnRegenRate?$AA@=007f7764
// @ref ?Add@?$DynamicVectorClass@PAVBuildingTypeClass@@@@QAE_NABQAVBuildingTypeClass@@@Z=0058eff0
// @ref ?Add@?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@QAE_NABQAVVoxelAnimTypeClass@@@Z=00653450
// @ref ?Emergency_Exit@@YIXH@Z=00691310
// @ref ?Get_Point@INIClass@@QBE?AUINIPoint3D@@PBD0ABU2@@Z=0050fa40
// @ref ?Get_UUID@INIClass@@QBE?AUGUID@@PBD0U2@@Z=0050da00
// @ref ?Unknown_00603D50@@YAHXZ=00603d50
// @ref __real@8@3ff98efa351294e9c800=007ad160
// @ref ?Clear@?$VectorClass@PAVVoxelAnimTypeClass@@@@UAEXXZ=006532b0
// @ref ?Clear@?$VectorClass@PAVAnimTypeClass@@@@UAEXXZ=0050b3f0
// @ref ?Clear@?$VectorClass@PAVBuildingTypeClass@@@@UAEXXZ=004f7100
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_03NIKF@ROT?$AA@=007d1404
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14
// @ref ??_C@_04IHF@Cost?$AA@=007dae28
// @ref ??_C@_05PDDA@Speed?$AA@=007d381c
// @ref ??_C@_06BMBE@Spawns?$AA@=007cee70
// @ref ??_C@_07NBFD@Palette?$AA@=007d9e2c
// @ref ??_C@_09FKED@TechLevel?$AA@=007da8bc
// @ref ??_C@_0L@CLCE@Normalized?$AA@=007cefc8
// @ref ??_C@_0L@PJAI@XXICON?4SHP?$AA@=007d61bc
// @ref __real@4@3ffe8000000000000000=0079dd80
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref __real@8@bfff8000000000000000=0079d578
// @ref ??B?$FixedString@$0BJ@@@QBEPBDXZ=0050b0e0
#include "shared/techno_type.hpp"
#include "shared/ccini_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/rules.hpp"
#include "shared/anim_type.hpp"
#include "shared/voxel_anim_type.hpp"
#include "shared/building_type.hpp"
#include "shared/unit_type.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/particle_system.hpp"
#include "shared/debug_printf.hpp"
#include "shared/exit.hpp"

// A recoil timing value (TurretTravel=, BarrelTravel=); the default is the
// current value.
static inline int Get_Recoil(CCINIClass &ini, char const *section, char const *entry, int value)
{
    value = ini.Get_Int(section, entry, value);
    return value;
}

// A recoil frame count (TurretCompressFrames= ...): at least one.
static inline int Get_Recoil_Frames(CCINIClass &ini, char const *section, char const *entry, int frames)
{
    frames = ini.Get_Int(section, entry, frames);
    if (frames <= 0) {
        return 1;
    }
    return frames;
}

bool TechnoTypeClass::Read_INI(CCINIClass &ini)
{
    if (ObjectTypeClass::Read_INI(ini)) {
        LandTargeting = ini.Get_Int(ID, "LandTargeting", LandTargeting);
        NavalTargeting = ini.Get_Int(ID, "NavalTargeting", NavalTargeting);
        SpeedType = ini.Get_SpeedType(ID, "SpeedType", (::SpeedType)SpeedType);
        TypeImmune = ini.Get_Bool(ID, "TypeImmune", TypeImmune);
        WalkRate = ini.Get_Int(ID, "WalkRate", WalkRate);
        IdleRate = ini.Get_Int(ID, "IdleRate", IdleRate);
        MoveToShroud = ini.Get_Bool(ID, "MoveToShroud", MoveToShroud);
        IsTrain = ini.Get_Bool(ID, "IsTrain", IsTrain);
        DoubleOwned = ini.Get_Bool(ID, "DoubleOwned", DoubleOwned);
        GuardRange.Value = ini.Get_Lepton(ID, "GuardRange", GuardRange.Value);
        Explodes = ini.Get_Bool(ID, "Explodes", Explodes);
        DeathWeapon = Get_Type(ini, ID, "DeathWeapon", DeathWeapon);
        DeathWeaponDamageModifier = ini.Get_Double(ID, "DeathWeaponDamageModifier", DeathWeaponDamageModifier);
        FlightLevel = ini.Get_Int(ID, "FlightLevel", FlightLevel);
        IsDropship = ini.Get_Bool(ID, "IsDropship", IsDropship);
        double pitch = ini.Get_Double(ID, "PitchAngle", -1.0);
        if (pitch != -1.0) {
            PitchAngle = pitch * (3.141592653589793 / 180.0);
        }
        double roll = ini.Get_Double(ID, "RollAngle", -1.0);
        if (roll != -1.0) {
            RollAngle = roll * (3.141592653589793 / 180.0);
        }
        PitchSpeed = ini.Get_Double(ID, "PitchSpeed", PitchSpeed);
        Locomotor = ini.Get_UUID(ID, "Locomotor", Locomotor);
        CloakingSpeed = ini.Get_Int(ID, "CloakingSpeed", CloakingSpeed);
        ThreatAvoidanceCoefficient = ini.Get_Double(ID, "ThreatAvoidanceCoefficient", ThreatAvoidanceCoefficient);
        SlowdownDistance = ini.Get_Int(ID, "SlowdownDistance", SlowdownDistance);
        DeaccelerationFactor = ini.Get_Double(ID, "DeaccelerationFactor", DeaccelerationFactor);
        AccelerationFactor = ini.Get_Double(ID, "AccelerationFactor", AccelerationFactor);
        Weight = ini.Get_Double(ID, "Weight", Weight);
        PhysicalSize = ini.Get_Double(ID, "PhysicalSize", PhysicalSize);
        Size = ini.Get_Double(ID, "Size", Size);
        SizeLimit = ini.Get_Double(ID, "SizeLimit", SizeLimit);
        HoverAttack = ini.Get_Bool(ID, "HoverAttack", HoverAttack);
        VHPScan = ini.Get_Level(ID, "VHPScan", (LevelType)VHPScan);
        MaxDebris = ini.Get_Int(ID, "MaxDebris", MaxDebris);
        MinDebris = ini.Get_Int(ID, "MinDebris", MinDebris);
        if (MinDebris < 0) {
            MinDebris = 0;
        }
        if (MaxDebris < MinDebris) {
            MaxDebris = MinDebris;
        }
        DebrisTypes = TypeListReader<VoxelAnimTypeClass>::Get(ini, ID, "DebrisTypes", DebrisTypes);
        DebrisMaximums = ini.Get_Integer_List(ID, "DebrisMaximums", DebrisMaximums);
        DebrisAnims = TypeListReader<AnimTypeClass>::Get(ini, ID, "DebrisAnims", DebrisAnims);
        HasTurretTooltips = ini.Get_Bool(ID, "HasTurretTooltips", HasTurretTooltips);
        TurretCount = ini.Get_Int(ID, "TurretCount", TurretCount);
        WeaponCount = ini.Get_Int(ID, "WeaponCount", WeaponCount);
        IsChargeTurret = ini.Get_Bool(ID, "IsChargeTurret", IsChargeTurret);
        ClearAllWeapons = ini.Get_Bool(ID, "ClearAllWeapons", ClearAllWeapons);
        if (TurretCount > 0) {
            for (int index = 0; index < WeaponCount; index++) {
                char weapon[12];
                char elite[16];
                sprintf(weapon, "Weapon%d", index + 1);
                sprintf(elite, "EliteWeapon%d", index + 1);
                Get_Weapon(index)->WeaponType = Get_Type(ini, ID, weapon, Get_Weapon(index)->WeaponType);
                Get_Elite_Weapon(index)->WeaponType = Get_Type(ini, ID, elite, Get_Elite_Weapon(index)->WeaponType);
            }
        } else if (!ClearAllWeapons) {
            Weapon[0].WeaponType = Get_Type(ini, ID, "Primary", Weapon[0].WeaponType);
            Weapon[1].WeaponType = Get_Type(ini, ID, "Secondary", Weapon[1].WeaponType);
            EliteWeapon[0].WeaponType = Get_Type(ini, ID, "ElitePrimary", EliteWeapon[0].WeaponType);
            EliteWeapon[1].WeaponType = Get_Type(ini, ID, "EliteSecondary", EliteWeapon[1].WeaponType);
        }
        if (ClearAllWeapons) {
            Weapon[0].WeaponType = 0;
            Weapon[1].WeaponType = 0;
            EliteWeapon[0].WeaponType = 0;
            EliteWeapon[1].WeaponType = 0;
        }
        VoiceMove = Get_Voc_List(ini, ID, "VoiceMove", VoiceMove);
        VoiceSelect = Get_Voc_List(ini, ID, "VoiceSelect", VoiceSelect);
        VoiceAttack = Get_Voc_List(ini, ID, "VoiceAttack", VoiceAttack);
        VoiceSpecialAttack = Get_Voc_List(ini, ID, "VoiceSpecialAttack", VoiceSpecialAttack);
        VoiceDie = Get_Voc_List(ini, ID, "VoiceDie", VoiceDie);
        VoiceFeedback = Get_Voc_List(ini, ID, "VoiceFeedback", VoiceFeedback);
        AuxSound1 = Get_Sound(ini, ID, "AuxSound1", AuxSound1);
        AuxSound2 = Get_Sound(ini, ID, "AuxSound2", AuxSound2);
        CreateSound = Get_Sound(ini, ID, "CreateSound", CreateSound);
        DamageSound = Get_Sound(ini, ID, "DamageSound", DamageSound);
        ImpactWaterSound = Get_Sound(ini, ID, "ImpactWaterSound", ImpactWaterSound);
        ImpactLandSound = Get_Sound(ini, ID, "ImpactLandSound", ImpactLandSound);
        CrashingSound = Get_Sound(ini, ID, "CrashingSound", CrashingSound);
        SinkingSound = Get_Sound(ini, ID, "SinkingSound", SinkingSound);
        VoiceFalling = Get_Sound(ini, ID, "VoiceFalling", VoiceFalling);
        VoiceCrashing = Get_Sound(ini, ID, "VoiceCrashing", VoiceCrashing);
        VoiceSinking = Get_Sound(ini, ID, "VoiceSinking", VoiceSinking);
        VoiceEnter = Get_Sound(ini, ID, "VoiceEnter", VoiceEnter);
        VoiceCapture = Get_Sound(ini, ID, "VoiceCapture", VoiceCapture);
        CloakStop = ini.Get_Bool(ID, "CloakStop", CloakStop);
        Storage = ini.Get_Int(ID, "Storage", Storage);
        BuildLimit = ini.Get_Int(ID, "BuildLimit", BuildLimit);
        Category = ini.Get_CategoryType(ID, "Category", (CategoryType)Category);
        Dock = TypeListReader<BuildingTypeClass>::Get(ini, ID, "Dock", Dock);
        DeploysInto = Get_Type(ini, ID, "DeploysInto", DeploysInto);
        UndeploysInto = Get_Type(ini, ID, "UndeploysInto", UndeploysInto);
        LightningRod = ini.Get_Bool(ID, "LightningRod", LightningRod);
        ManualReload = ini.Get_Bool(ID, "ManualReload", ManualReload);
        TurretSpins = ini.Get_Bool(ID, "TurretSpins", TurretSpins);
        Turret = ini.Get_Bool(ID, "Turret", Turret);
        TurretRotateSound = Get_Sound(ini, ID, "TurretRotateSound", TurretRotateSound);
        EnterTransportSound = Get_Sound(ini, ID, "EnterTransportSound", EnterTransportSound);
        LeaveTransportSound = Get_Sound(ini, ID, "LeaveTransportSound", LeaveTransportSound);
        MoveSound = Get_Voc_List(ini, ID, "MoveSound", MoveSound);
        DieSound = Get_Voc_List(ini, ID, "DieSound", DieSound);
        DeploySound = Get_Sound(ini, ID, "DeploySound", DeploySound);
        UndeploySound = Get_Sound(ini, ID, "UndeploySound", UndeploySound);
        ChronoInSound = Get_Sound(ini, ID, "ChronoInSound", ChronoInSound);
        ChronoOutSound = Get_Sound(ini, ID, "ChronoOutSound", ChronoOutSound);
        Explosion = TypeListReader<AnimTypeClass>::Get(ini, ID, "Explosion", Explosion);
        DestroyAnim = TypeListReader<AnimTypeClass>::Get(ini, ID, "DestroyAnim", DestroyAnim);
        NaturalParticleSystem = Get_Type(ini, ID, "NaturalParticleSystem", NaturalParticleSystem);
        (INIPoint3D &)NaturalParticleLocation = ini.Get_Integer_Triple(ID, "NaturalParticleLocation", (INIPoint3D &)NaturalParticleLocation);
        DamageParticleSystems = TypeListReader<ParticleSystemTypeClass>::Get(ini, ID, "DamageParticleSystems", DamageParticleSystems);
        DestroyParticleSystems = TypeListReader<ParticleSystemTypeClass>::Get(ini, ID, "DestroyParticleSystems", DestroyParticleSystems);
        (INIPoint3D &)DamageSmokeOffset = ini.Get_Integer_Triple(ID, "DamageSmokeOffset", (INIPoint3D &)DamageSmokeOffset);
        DamSmkOffScrnRel = ini.Get_Bool(ID, "DamSmkOffScrnRel", DamSmkOffScrnRel);
        (INIPoint3D &)DestroySmokeOffset = ini.Get_Integer_Triple(ID, "DestroySmokeOffset", (INIPoint3D &)DestroySmokeOffset);
        (INIPoint3D &)RefnSmokeOffsetOne = ini.Get_Integer_Triple(ID, "RefnSmokeOffsetOne", (INIPoint3D &)RefnSmokeOffsetOne);
        (INIPoint3D &)RefnSmokeOffsetTwo = ini.Get_Integer_Triple(ID, "RefnSmokeOffsetTwo", (INIPoint3D &)RefnSmokeOffsetTwo);
        Nominal = ini.Get_Bool(ID, "Nominal", Nominal);
        Cloakable = ini.Get_Bool(ID, "Cloakable", Cloakable);
        GapGenerator = ini.Get_Bool(ID, "GapGenerator", GapGenerator);
        GapRadiusInCells = ini.Get_Int(ID, "GapRadiusInCells", GapRadiusInCells);
        SuperGapRadiusInCells = ini.Get_Int(ID, "SuperGapRadiusInCells", SuperGapRadiusInCells);
        Teleporter = ini.Get_Bool(ID, "Teleporter", Teleporter);
        Sensors = ini.Get_Bool(ID, "Sensors", Sensors);
        PipScale = ini.Get_PipScale(ID, "PipScale", PipScale);
        PipWrap = ini.Get_Int(ID, "PipWrap", PipWrap);
        Prerequisite = Get_Prerequisite_List(ini, ID, "Prerequisite", Prerequisite);
        PrerequisiteOverride = Get_Prerequisite_List(ini, ID, "PrerequisiteOverride", PrerequisiteOverride);
        Sight = ini.Get_Int(ID, "Sight", Sight);
        ReselectIfLimboed = ini.Get_Bool(ID, "ReselectIfLimboed", ReselectIfLimboed);
        RejoinTeamIfLimboed = ini.Get_Bool(ID, "RejoinTeamIfLimboed", RejoinTeamIfLimboed);
        SensorsSight = ini.Get_Int(ID, "SensorsSight", SensorsSight);
        DetectDisguiseRange = ini.Get_Int(ID, "DetectDisguiseRange", DetectDisguiseRange);
        BombSight = ini.Get_Int(ID, "BombSight", BombSight);
        LeadershipRating = ini.Get_Int(ID, "LeadershipRating", LeadershipRating);
        RevealToAll = ini.Get_Bool(ID, "RevealToAll", RevealToAll);
        CanDisguise = ini.Get_Bool(ID, "CanDisguise", CanDisguise);
        PermaDisguise = ini.Get_Bool(ID, "PermaDisguise", PermaDisguise);
        DetectDisguise = ini.Get_Bool(ID, "DetectDisguise", DetectDisguise);
        DisguiseWhenStill = ini.Get_Bool(ID, "DisguiseWhenStill", DisguiseWhenStill);
        CanPassiveAquire = ini.Get_Bool(ID, "CanPassiveAquire", CanPassiveAquire);
        CanRetaliate = ini.Get_Bool(ID, "CanRetaliate", CanRetaliate);
        CanApproachTarget = ini.Get_Bool(ID, "CanApproachTarget", CanApproachTarget);
        CanRecalcApproachTarget = ini.Get_Bool(ID, "CanRecalcApproachTarget", CanRecalcApproachTarget);
        RequiresStolenSovietTech = ini.Get_Bool(ID, "RequiresStolenSovietTech", RequiresStolenSovietTech);
        RequiresStolenAlliedTech = ini.Get_Bool(ID, "RequiresStolenAlliedTech", RequiresStolenAlliedTech);
        RequiredHouses = ini.Get_Owners(ID, "RequiredHouses", RequiredHouses);
        ForbiddenHouses = ini.Get_Owners(ID, "ForbiddenHouses", ForbiddenHouses);
        TechLevel = ini.Get_Int(ID, "TechLevel", TechLevel);
        int speed = ini.Get_Int(ID, "Speed", -1);
        if (speed != -1) {
            if (speed >= 100) {
                speed = 100;
            }
            speed = speed <= 0 ? 0 : speed;
            int value = speed * 256 / 100;
            Speed = value < 255 ? value : 255;
        }
        Cost = ini.Get_Int(ID, "Cost", Cost);
        Soylent = ini.Get_Int(ID, "Soylent", Soylent);
        UnloadingClass = Get_Type(ini, ID, "UnloadingClass", UnloadingClass);
        InitialAmmo = ini.Get_Int(ID, "InitialAmmo", InitialAmmo);
        Ammo = ini.Get_Int(ID, "Ammo", Ammo);
        IFVMode = ini.Get_Int(ID, "IFVMode", IFVMode);
        AirRangeBonus = ini.Get_Lepton(ID, "AirRangeBonus", AirRangeBonus);
        RadialFireSegments = ini.Get_Int(ID, "RadialFireSegments", RadialFireSegments);
        DeployFireWeapon = ini.Get_Int(ID, "DeployFireWeapon", DeployFireWeapon);
        DeployFire = ini.Get_Bool(ID, "DeployFire", DeployFire);
        MobileFire = ini.Get_Bool(ID, "MobileFire", MobileFire);
        OpportunityFire = ini.Get_Bool(ID, "OpportunityFire", OpportunityFire);
        DistributedFire = ini.Get_Bool(ID, "DistributedFire", DistributedFire);
        Reload = ini.Get_Int(ID, "Reload", Reload);
        EmptyReload = ini.Get_Int(ID, "EmptyReload", EmptyReload);
        ReloadIncrement = ini.Get_Int(ID, "ReloadIncrement", ReloadIncrement);
        DamageReducesReadiness = ini.Get_Bool(ID, "DamageReducesReadiness", DamageReducesReadiness);
        ReadinessReductionMultiplier = ini.Get_Double(ID, "ReadinessReductionMultiplier", ReadinessReductionMultiplier);
        PreventAttackMove = ini.Get_Bool(ID, "PreventAttackMove", PreventAttackMove);
        Points = ini.Get_Int(ID, "Points", Points);
        unknown_59c = Points;
        ThreatPosed = ini.Get_Int(ID, "ThreatPosed", ThreatPosed);
        Owner = ini.Get_Owners(ID, "Owner", Owner);
        AIBasePlanningSide = ini.Get_Int(ID, "AIBasePlanningSide", AIBasePlanningSide);
        Trainable = ini.Get_Bool(ID, "Trainable", Trainable);
        Crewed = ini.Get_Bool(ID, "Crewed", Crewed);
        Gunner = ini.Get_Bool(ID, "Gunner", Gunner);
        Naval = ini.Get_Bool(ID, "Naval", Naval);
        Repairable = ini.Get_Bool(ID, "Repairable", Repairable);
        Invisible = ini.Get_Bool(ID, "Invisible", Invisible);
        RadarVisible = ini.Get_Bool(ID, "RadarVisible", RadarVisible);
        SelfHealing = ini.Get_Bool(ID, "SelfHealing", SelfHealing);
        NoAutoFire = ini.Get_Bool(ID, "NoAutoFire", NoAutoFire);
        ROT = ini.Get_Int(ID, "ROT", ROT);
        Passengers = ini.Get_Int(ID, "Passengers", Passengers);
        FireAngle = ini.Get_Int(ID, "FireAngle", FireAngle);
        DeployTime = ini.Get_Double(ID, "DeployTime", DeployTime);
        UndeployDelay = ini.Get_Int(ID, "UndeployDelay", UndeployDelay);
        Disableable = ini.Get_Bool(ID, "Disableable", Disableable);
        ToProtect = ini.Get_Bool(ID, "ToProtect", ToProtect);
        TiberiumHeal = ini.Get_Bool(ID, "TiberiumHeal", TiberiumHeal);
        ImmuneToVeins = ini.Get_Bool(ID, "ImmuneToVeins", ImmuneToVeins);
        AllowedToStartInMultiplayer = ini.Get_Bool(ID, "AllowedToStartInMultiplayer", AllowedToStartInMultiplayer);
        StupidHunt = ini.Get_Bool(ID, "StupidHunt", StupidHunt);
        TargetLaser = ini.Get_Bool(ID, "TargetLaser", TargetLaser);
        HunterSeeker = ini.Get_Bool(ID, "HunterSeeker", HunterSeeker);
        Crusher = ini.Get_Bool(ID, "Crusher", Crusher);
        AutoCrush = ini.Get_Bool(ID, "AutoCrush", AutoCrush);
        ImmuneToRadiation = ini.Get_Bool(ID, "ImmuneToRadiation", ImmuneToRadiation);
        Spawned = ini.Get_Bool(ID, "Spawned", Spawned);
        Underwater = ini.Get_Bool(ID, "Underwater", Underwater);
        BalloonHover = ini.Get_Bool(ID, "BalloonHover", BalloonHover);
        Spawns = Get_Type(ini, ID, "Spawns", Spawns);
        SpawnRegenRate = ini.Get_Int(ID, "SpawnRegenRate", SpawnRegenRate);
        SpawnsNumber = ini.Get_Int(ID, "SpawnsNumber", SpawnsNumber);
        SpawnReloadRate = ini.Get_Int(ID, "SpawnReloadRate", SpawnReloadRate);
        MissileSpawn = ini.Get_Bool(ID, "MissileSpawn", MissileSpawn);
        DefaultToGuardArea = ini.Get_Bool(ID, "DefaultToGuardArea", DefaultToGuardArea);
        Warpable = ini.Get_Bool(ID, "Warpable", Warpable);
        Parasiteable = ini.Get_Bool(ID, "Parasiteable", Parasiteable);
        ImmuneToPsionics = ini.Get_Bool(ID, "ImmuneToPsionics", ImmuneToPsionics);
        ConsideredAircraft = ini.Get_Bool(ID, "ConsideredAircraft", ConsideredAircraft);
        Organic = ini.Get_Bool(ID, "Organic", Organic);
        SuppressionThreshold = ini.Get_Int(ID, "SuppressionThreshold", SuppressionThreshold);
        NoShadow = ini.Get_Bool(ID, "NoShadow", NoShadow);
        JumpjetTurnRate = ini.Get_Int(ID, "JumpjetTurnRate", JumpjetTurnRate);
        JumpjetSpeed = ini.Get_Int(ID, "JumpjetSpeed", JumpjetSpeed);
        JumpjetClimb = ini.Get_Double(ID, "JumpjetClimb", JumpjetClimb);
        JumpjetCrash = ini.Get_Double(ID, "JumpjetCrash", JumpjetCrash);
        JumpjetHeight = ini.Get_Int(ID, "JumpjetHeight", JumpjetHeight);
        JumpjetAccel = ini.Get_Double(ID, "JumpjetAccel", JumpjetAccel);
        JumpjetWobbles = ini.Get_Double(ID, "JumpjetWobbles", JumpjetWobbles);
        JumpjetNoWobbles = ini.Get_Bool(ID, "JumpjetNoWobbles", JumpjetNoWobbles);
        JumpjetDeviation = ini.Get_Int(ID, "JumpjetDeviation", JumpjetDeviation);
        JumpJet = ini.Get_Bool(ID, "JumpJet", JumpJet);
        Crashable = ini.Get_Bool(ID, "Crashable", Crashable);
        AttackFriendlies = ini.Get_Bool(ID, "AttackFriendlies", AttackFriendlies);
        AttackCursorOnFriendlies = ini.Get_Bool(ID, "AttackCursorOnFriendlies", AttackCursorOnFriendlies);
        TurretRecoil = ini.Get_Bool(ID, "TurretRecoil", TurretRecoil);
        TurretAnimData.Travel = Get_Recoil(ini, ID, "TurretTravel", TurretAnimData.Travel);
        TurretAnimData.CompressFrames = Get_Recoil_Frames(ini, ID, "TurretCompressFrames", TurretAnimData.CompressFrames);
        TurretAnimData.HoldFrames = Get_Recoil_Frames(ini, ID, "TurretHoldFrames", TurretAnimData.HoldFrames);
        TurretAnimData.RecoverFrames = Get_Recoil_Frames(ini, ID, "TurretRecoverFrames", TurretAnimData.RecoverFrames);
        BarrelAnimData = TurretAnimData;
        BarrelAnimData.Travel = Get_Recoil(ini, ID, "BarrelTravel", TurretAnimData.Travel);
        BarrelAnimData.CompressFrames = Get_Recoil_Frames(ini, ID, "BarrelCompressFrames", TurretAnimData.CompressFrames);
        BarrelAnimData.HoldFrames = Get_Recoil_Frames(ini, ID, "BarrelHoldFrames", TurretAnimData.HoldFrames);
        BarrelAnimData.RecoverFrames = Get_Recoil_Frames(ini, ID, "BarrelRecoverFrames", TurretAnimData.RecoverFrames);
        TiltsWhenCrushes = ini.Get_Bool(ID, "TiltsWhenCrushes", TiltsWhenCrushes);
        Accelerates = ini.Get_Bool(ID, "Accelerates", Accelerates);
        ZFudgeCliff = ini.Get_Int(ID, "ZFudgeCliff", ZFudgeCliff);
        ZFudgeColumn = ini.Get_Int(ID, "ZFudgeColumn", ZFudgeColumn);
        ZFudgeTunnel = ini.Get_Int(ID, "ZFudgeTunnel", ZFudgeTunnel);
        ZFudgeBridge = ini.Get_Int(ID, "ZFudgeBridge", ZFudgeBridge);
        VeteranAbilities = ini.Get_Abilities(ID, "VeteranAbilities", VeteranAbilities);
        EliteAbilities = ini.Get_Abilities(ID, "EliteAbilities", EliteAbilities);
        MyEffectivenessCoefficient = ini.Get_Double(ID, "MyEffectivenessCoefficient", MyEffectivenessCoefficient == 0.0 ? Rules->unknown_d00 : MyEffectivenessCoefficient);
        TargetEffectivenessCoefficient = ini.Get_Double(ID, "TargetEffectivenessCoefficient", TargetEffectivenessCoefficient == 0.0 ? Rules->unknown_d08 : TargetEffectivenessCoefficient);
        TargetSpecialThreatCoefficient = ini.Get_Double(ID, "TargetSpecialThreatCoefficient", TargetSpecialThreatCoefficient == 0.0 ? Rules->unknown_d10 : TargetSpecialThreatCoefficient);
        TargetStrengthCoefficient = ini.Get_Double(ID, "TargetStrengthCoefficient", TargetStrengthCoefficient == 0.0 ? Rules->unknown_d18 : TargetStrengthCoefficient);
        TargetDistanceCoefficient = ini.Get_Double(ID, "TargetDistanceCoefficient", TargetDistanceCoefficient == 0.0 ? Rules->unknown_d20 : TargetDistanceCoefficient);
        SpecialThreatValue = ini.Get_Double(ID, "SpecialThreatValue", SpecialThreatValue);
        IsSelectableCombatant = ini.Get_Bool(ID, "IsSelectableCombatant", IsSelectableCombatant);

        unknown_aa8 = false;
        if (Weapon[0].WeaponType != 0 && Weapon[0].WeaponType->unknown_a4 > 0) {
            unknown_aa8 = true;
        }

        char fullname[512];
        _makepath(fullname, 0, 0, unknown_1c8, ".SHP");
        if (unknown_a8 && unknown_a4 != 0) {
            delete unknown_a4;
            unknown_a4 = 0;
            unknown_a8 = false;
        }
        unknown_a4 = (void *)MixFileClass<CCFileClass>::Retrieve(fullname);

        ArtINI.Get_String(unknown_1c8, "Palette", "", PaletteFile.Buffer, sizeof(PaletteFile.Buffer));
        Load_Palette();
        if (Unknown_00603D50() > 1) {
            Debug_Printf("You have violated the limit of having only one extra building palette.\n");
            Emergency_Exit(-1);
        }
        TurretOffset = ArtINI.Get_Int(unknown_1c8, "TurretOffset", TurretOffset);
        RotCount = ArtINI.Get_Int(unknown_1c8, "RotCount", RotCount);
        Remapable = ArtINI.Get_Bool(unknown_1c8, "Remapable", Remapable);
        Normalized = ArtINI.Get_Bool(unknown_1c8, "Normalized", Normalized);
        VisibleLoad = ArtINI.Get_Bool(unknown_1c8, "VisibleLoad", VisibleLoad);
        ShadowIndex = ArtINI.Get_Int(unknown_1c8, "ShadowIndex", ShadowIndex);
        DisableVoxelCache = ArtINI.Get_Bool(unknown_1c8, "DisableVoxelCache", DisableVoxelCache);
        DisableShadowCache = ArtINI.Get_Bool(unknown_1c8, "DisableShadowCache", DisableShadowCache);
        char cameo[32];
        ArtINI.Get_String(unknown_1c8, "Cameo", "", cameo, sizeof(CameoFile));
        if (strlen(cameo) != 0) {
            strcpy(CameoFile.Buffer, cameo);
            _makepath(fullname, 0, 0, CameoFile, ".SHP");
            if (CameoData == 0) {
                CameoData = (void *)MixFileClass<CCFileClass>::Retrieve(fullname);
            }
        }
        if (CameoData == 0) {
            CameoData = (void *)MixFileClass<CCFileClass>::Retrieve("XXICON.SHP");
        }
        ArtINI.Get_String(unknown_1c8, "AltCameo", "", cameo, sizeof(AltCameoFile));
        if (strlen(cameo) != 0) {
            strcpy(AltCameoFile.Buffer, cameo);
            _makepath(fullname, 0, 0, AltCameoFile, ".SHP");
            if (AltCameoData == 0) {
                AltCameoData = (void *)MixFileClass<CCFileClass>::Retrieve(fullname);
            }
        }

        if (TurretCount > 0) {
            for (int index = 0; index < WeaponCount; index++) {
                char weapon[32];
                char entry[128];
                sprintf(weapon, "Weapon%d", index + 1);
                sprintf(entry, "%sFLH", weapon);
                (INIPoint3D &)Get_Weapon(index)->FLH = ArtINI.Get_Point(unknown_1c8, entry, (INIPoint3D &)Get_Weapon(index)->FLH);
                sprintf(entry, "%sBarrelLength", weapon);
                Get_Weapon(index)->BarrelLength = ArtINI.Get_Int(unknown_1c8, entry, Get_Weapon(index)->BarrelLength);
                sprintf(entry, "%sBarrelThickness", weapon);
                Get_Weapon(index)->BarrelThickness = ArtINI.Get_Int(unknown_1c8, entry, Get_Weapon(index)->BarrelThickness);
                sprintf(entry, "%sTurretLocked", weapon);
                Get_Weapon(index)->TurretLocked = ArtINI.Get_Bool(unknown_1c8, entry, Get_Weapon(index)->TurretLocked);

                sprintf(weapon, "EliteWeapon%d", index + 1);
                sprintf(entry, "%sFLH", weapon);
                (INIPoint3D &)Get_Elite_Weapon(index)->FLH = ArtINI.Get_Point(unknown_1c8, entry, (INIPoint3D &)Get_Weapon(index)->FLH);
                sprintf(entry, "%sBarrelLength", weapon);
                Get_Elite_Weapon(index)->BarrelLength = ArtINI.Get_Int(unknown_1c8, entry, Get_Weapon(index)->BarrelLength);
                sprintf(entry, "%sBarrelThickness", weapon);
                Get_Elite_Weapon(index)->BarrelThickness = ArtINI.Get_Int(unknown_1c8, entry, Get_Weapon(index)->BarrelThickness);
                sprintf(entry, "%sTurretLocked", weapon);
                Get_Elite_Weapon(index)->TurretLocked = ArtINI.Get_Bool(unknown_1c8, entry, Get_Weapon(index)->TurretLocked);
            }
        } else {
            (INIPoint3D &)Weapon[0].FLH = ArtINI.Get_Point(unknown_1c8, "PrimaryFireFLH", (INIPoint3D &)Weapon[0].FLH);
            Weapon[0].BarrelLength = ArtINI.Get_Int(unknown_1c8, "PBarrelLength", Weapon[0].BarrelLength);
            Weapon[0].BarrelThickness = ArtINI.Get_Int(unknown_1c8, "PBarrelThickness", Weapon[0].BarrelThickness);
            (INIPoint3D &)Weapon[1].FLH = ArtINI.Get_Point(unknown_1c8, "SecondaryFireFLH", (INIPoint3D &)Weapon[1].FLH);
            Weapon[1].BarrelLength = ArtINI.Get_Int(unknown_1c8, "SBarrelLength", Weapon[1].BarrelLength);
            Weapon[1].BarrelThickness = ArtINI.Get_Int(unknown_1c8, "SBarrelThickness", Weapon[1].BarrelThickness);
            (INIPoint3D &)EliteWeapon[0].FLH = ArtINI.Get_Point(unknown_1c8, "ElitePrimaryFireFLH", (INIPoint3D &)Weapon[0].FLH);
            EliteWeapon[0].BarrelLength = ArtINI.Get_Int(unknown_1c8, "ElitePBarrelLength", Weapon[0].BarrelLength);
            EliteWeapon[0].BarrelThickness = ArtINI.Get_Int(unknown_1c8, "ElitePBarrelThickness", Weapon[0].BarrelThickness);
            (INIPoint3D &)EliteWeapon[1].FLH = ArtINI.Get_Point(unknown_1c8, "EliteSecondaryFireFLH", (INIPoint3D &)Weapon[1].FLH);
            EliteWeapon[1].BarrelLength = ArtINI.Get_Int(unknown_1c8, "EliteSBarrelLength", Weapon[1].BarrelLength);
            EliteWeapon[1].BarrelThickness = ArtINI.Get_Int(unknown_1c8, "EliteSBarrelThickness", Weapon[1].BarrelThickness);
        }
        TurretNotExportedOnGround = ArtINI.Get_Bool(unknown_1c8, "TurretNotExportedOnGround", TurretNotExportedOnGround);
        MovementZone = ini.Get_MovementZone(ID, "MovementZone", MovementZone);
        unknown_af5 = MovementZone == 6;

        if (unknown_206) {
            unknown_func_5d6730();
        } else if (Turret) {
            unknown_func_5d72b0();
        }
        if (unknown_b0.unknown_00 != 0 && !unknown_b0.unknown_00->unknown_00) {
            unknown_330 = unknown_b0.unknown_00->unknown_719860(0, 0)->unknown_a1 * 0.5f + 0.5;
            unknown_338 = unknown_b0.unknown_00->unknown_719860(0, 0)->unknown_a0 * 0.5f;
        }

        return true;
    }
    return false;
}
