    function targMap = targDataMap(),

    ;%***********************
    ;% Create Parameter Map *
    ;%***********************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 7;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc paramMap
        ;%
        paramMap.nSections           = nTotSects;
        paramMap.sectIdxOffset       = sectIdxOffset;
            paramMap.sections(nTotSects) = dumSection; %prealloc
        paramMap.nTotData            = -1;

        ;%
        ;% Auto data (rtP)
        ;%
            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtP.scenario
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtP.road
                    section.data(1).logicalSrcIdx = 1;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            paramMap.sections(2) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtP.model
                    section.data(1).logicalSrcIdx = 2;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            paramMap.sections(3) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtP.control
                    section.data(1).logicalSrcIdx = 3;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            paramMap.sections(4) = section;
            clear section

            section.nData     = 124;
            section.data(124)  = dumData; %prealloc

                    ;% rtP.Constant_Value
                    section.data(1).logicalSrcIdx = 4;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.gear_Y0
                    section.data(2).logicalSrcIdx = 5;
                    section.data(2).dtTransOffset = 1;

                    ;% rtP.u_vgt_Y0
                    section.data(3).logicalSrcIdx = 6;
                    section.data(3).dtTransOffset = 2;

                    ;% rtP.u_egr_Y0
                    section.data(4).logicalSrcIdx = 7;
                    section.data(4).dtTransOffset = 3;

                    ;% rtP.u_delta_Y0
                    section.data(5).logicalSrcIdx = 8;
                    section.data(5).dtTransOffset = 4;

                    ;% rtP.F_brake_Y0
                    section.data(6).logicalSrcIdx = 9;
                    section.data(6).dtTransOffset = 5;

                    ;% rtP.Saturation_UpperSat
                    section.data(7).logicalSrcIdx = 10;
                    section.data(7).dtTransOffset = 6;

                    ;% rtP.Saturation_LowerSat
                    section.data(8).logicalSrcIdx = 11;
                    section.data(8).dtTransOffset = 7;

                    ;% rtP.brake_Value
                    section.data(9).logicalSrcIdx = 12;
                    section.data(9).dtTransOffset = 8;

                    ;% rtP.Constant_Value_eler4bv4qe
                    section.data(10).logicalSrcIdx = 13;
                    section.data(10).dtTransOffset = 9;

                    ;% rtP.Integrator_IC
                    section.data(11).logicalSrcIdx = 14;
                    section.data(11).dtTransOffset = 10;

                    ;% rtP.Integrator_UpperSat
                    section.data(12).logicalSrcIdx = 15;
                    section.data(12).dtTransOffset = 11;

                    ;% rtP.Integrator_LowerSat
                    section.data(13).logicalSrcIdx = 16;
                    section.data(13).dtTransOffset = 12;

                    ;% rtP.mskmh_Gain
                    section.data(14).logicalSrcIdx = 17;
                    section.data(14).dtTransOffset = 13;

                    ;% rtP.Integrator1_IC
                    section.data(15).logicalSrcIdx = 18;
                    section.data(15).dtTransOffset = 14;

                    ;% rtP.Integrator1_UpperSat
                    section.data(16).logicalSrcIdx = 19;
                    section.data(16).dtTransOffset = 15;

                    ;% rtP.Integrator1_LowerSat
                    section.data(17).logicalSrcIdx = 20;
                    section.data(17).dtTransOffset = 16;

                    ;% rtP.Gain1_Gain
                    section.data(18).logicalSrcIdx = 21;
                    section.data(18).dtTransOffset = 17;

                    ;% rtP.Gain2_Gain
                    section.data(19).logicalSrcIdx = 22;
                    section.data(19).dtTransOffset = 18;

                    ;% rtP.PulseGenerator_Amp
                    section.data(20).logicalSrcIdx = 23;
                    section.data(20).dtTransOffset = 19;

                    ;% rtP.PulseGenerator_Period
                    section.data(21).logicalSrcIdx = 24;
                    section.data(21).dtTransOffset = 20;

                    ;% rtP.PulseGenerator_Duty
                    section.data(22).logicalSrcIdx = 25;
                    section.data(22).dtTransOffset = 21;

                    ;% rtP.PulseGenerator_PhaseDelay
                    section.data(23).logicalSrcIdx = 26;
                    section.data(23).dtTransOffset = 22;

                    ;% rtP.Gain3_Gain
                    section.data(24).logicalSrcIdx = 27;
                    section.data(24).dtTransOffset = 23;

                    ;% rtP.Gain4_Gain
                    section.data(25).logicalSrcIdx = 28;
                    section.data(25).dtTransOffset = 24;

                    ;% rtP.Integratoromega_t_UpperSat
                    section.data(26).logicalSrcIdx = 29;
                    section.data(26).dtTransOffset = 25;

                    ;% rtP.Integratoromega_t_LowerSat
                    section.data(27).logicalSrcIdx = 30;
                    section.data(27).dtTransOffset = 26;

                    ;% rtP.Saturation_UpperSat_i32xa2dnvv
                    section.data(28).logicalSrcIdx = 31;
                    section.data(28).dtTransOffset = 27;

                    ;% rtP.Saturation_LowerSat_f5etl5uivq
                    section.data(29).logicalSrcIdx = 32;
                    section.data(29).dtTransOffset = 28;

                    ;% rtP.Gain6_Gain
                    section.data(30).logicalSrcIdx = 33;
                    section.data(30).dtTransOffset = 29;

                    ;% rtP.Gain5_Gain
                    section.data(31).logicalSrcIdx = 34;
                    section.data(31).dtTransOffset = 30;

                    ;% rtP.Integrator1_IC_mck3mtbbq3
                    section.data(32).logicalSrcIdx = 35;
                    section.data(32).dtTransOffset = 31;

                    ;% rtP.Integrator1_UpperSat_pktoycczal
                    section.data(33).logicalSrcIdx = 36;
                    section.data(33).dtTransOffset = 32;

                    ;% rtP.Integrator1_LowerSat_ofks0duo33
                    section.data(34).logicalSrcIdx = 37;
                    section.data(34).dtTransOffset = 33;

                    ;% rtP.radsRPM_Gain
                    section.data(35).logicalSrcIdx = 38;
                    section.data(35).dtTransOffset = 34;

                    ;% rtP.Gain8_Gain
                    section.data(36).logicalSrcIdx = 39;
                    section.data(36).dtTransOffset = 35;

                    ;% rtP.Gain9_Gain
                    section.data(37).logicalSrcIdx = 40;
                    section.data(37).dtTransOffset = 36;

                    ;% rtP.radsRPM_Gain_edopox2oep
                    section.data(38).logicalSrcIdx = 41;
                    section.data(38).dtTransOffset = 37;

                    ;% rtP.Memory3_InitialCondition
                    section.data(39).logicalSrcIdx = 42;
                    section.data(39).dtTransOffset = 38;

                    ;% rtP.Saturation_UpperSat_enesi2iumz
                    section.data(40).logicalSrcIdx = 43;
                    section.data(40).dtTransOffset = 39;

                    ;% rtP.Saturation_LowerSat_bn3le4gtty
                    section.data(41).logicalSrcIdx = 44;
                    section.data(41).dtTransOffset = 40;

                    ;% rtP.Switch_Threshold
                    section.data(42).logicalSrcIdx = 45;
                    section.data(42).dtTransOffset = 41;

                    ;% rtP.Saturation_UpperSat_hto0bhsqhd
                    section.data(43).logicalSrcIdx = 46;
                    section.data(43).dtTransOffset = 42;

                    ;% rtP.Saturation1_UpperSat
                    section.data(44).logicalSrcIdx = 47;
                    section.data(44).dtTransOffset = 43;

                    ;% rtP.Saturation1_LowerSat
                    section.data(45).logicalSrcIdx = 48;
                    section.data(45).dtTransOffset = 44;

                    ;% rtP.Memory2_InitialCondition
                    section.data(46).logicalSrcIdx = 49;
                    section.data(46).dtTransOffset = 45;

                    ;% rtP.Saturation_UpperSat_atvgvohnm4
                    section.data(47).logicalSrcIdx = 50;
                    section.data(47).dtTransOffset = 46;

                    ;% rtP.Saturation_LowerSat_bnot2t5v4i
                    section.data(48).logicalSrcIdx = 51;
                    section.data(48).dtTransOffset = 47;

                    ;% rtP.IntegratorX_Oim_IC
                    section.data(49).logicalSrcIdx = 52;
                    section.data(49).dtTransOffset = 48;

                    ;% rtP.IntegratorX_Oim_UpperSat
                    section.data(50).logicalSrcIdx = 53;
                    section.data(50).dtTransOffset = 49;

                    ;% rtP.IntegratorX_Oim_LowerSat
                    section.data(51).logicalSrcIdx = 54;
                    section.data(51).dtTransOffset = 50;

                    ;% rtP.Integrator_IC_ikgusueg51
                    section.data(52).logicalSrcIdx = 55;
                    section.data(52).dtTransOffset = 51;

                    ;% rtP.n_eratio_Gain
                    section.data(53).logicalSrcIdx = 56;
                    section.data(53).dtTransOffset = 52;

                    ;% rtP.GainM_e_Gain
                    section.data(54).logicalSrcIdx = 57;
                    section.data(54).dtTransOffset = 53;

                    ;% rtP.Saturation_UpperSat_fgktzvfm2k
                    section.data(55).logicalSrcIdx = 58;
                    section.data(55).dtTransOffset = 54;

                    ;% rtP.Saturation_LowerSat_eegm4iokxr
                    section.data(56).logicalSrcIdx = 59;
                    section.data(56).dtTransOffset = 55;

                    ;% rtP.BrakeGain_Gain
                    section.data(57).logicalSrcIdx = 60;
                    section.data(57).dtTransOffset = 56;

                    ;% rtP.Relay1_OnVal
                    section.data(58).logicalSrcIdx = 61;
                    section.data(58).dtTransOffset = 57;

                    ;% rtP.Relay1_OffVal
                    section.data(59).logicalSrcIdx = 62;
                    section.data(59).dtTransOffset = 58;

                    ;% rtP.Relay1_YOn
                    section.data(60).logicalSrcIdx = 63;
                    section.data(60).dtTransOffset = 59;

                    ;% rtP.Relay1_YOff
                    section.data(61).logicalSrcIdx = 64;
                    section.data(61).dtTransOffset = 60;

                    ;% rtP.Relay2_OnVal
                    section.data(62).logicalSrcIdx = 65;
                    section.data(62).dtTransOffset = 61;

                    ;% rtP.Relay2_OffVal
                    section.data(63).logicalSrcIdx = 66;
                    section.data(63).dtTransOffset = 62;

                    ;% rtP.Relay2_YOn
                    section.data(64).logicalSrcIdx = 67;
                    section.data(64).dtTransOffset = 63;

                    ;% rtP.Relay2_YOff
                    section.data(65).logicalSrcIdx = 68;
                    section.data(65).dtTransOffset = 64;

                    ;% rtP.Saturation_UpperSat_ehbc0hou2u
                    section.data(66).logicalSrcIdx = 69;
                    section.data(66).dtTransOffset = 65;

                    ;% rtP.Saturation_LowerSat_e2gfsq1ep3
                    section.data(67).logicalSrcIdx = 70;
                    section.data(67).dtTransOffset = 66;

                    ;% rtP.Saturation1_UpperSat_haikx2purp
                    section.data(68).logicalSrcIdx = 71;
                    section.data(68).dtTransOffset = 67;

                    ;% rtP.Saturation1_LowerSat_ja3qpjhkdu
                    section.data(69).logicalSrcIdx = 72;
                    section.data(69).dtTransOffset = 68;

                    ;% rtP.Memory1_InitialCondition
                    section.data(70).logicalSrcIdx = 73;
                    section.data(70).dtTransOffset = 69;

                    ;% rtP.Saturation_UpperSat_imjkncmbbp
                    section.data(71).logicalSrcIdx = 74;
                    section.data(71).dtTransOffset = 70;

                    ;% rtP.Saturation_LowerSat_jenqmbtgcj
                    section.data(72).logicalSrcIdx = 75;
                    section.data(72).dtTransOffset = 71;

                    ;% rtP.Switch_Threshold_oyf5ishr1i
                    section.data(73).logicalSrcIdx = 76;
                    section.data(73).dtTransOffset = 72;

                    ;% rtP.IntegratorX_Oem_IC
                    section.data(74).logicalSrcIdx = 77;
                    section.data(74).dtTransOffset = 73;

                    ;% rtP.IntegratorX_Oem_UpperSat
                    section.data(75).logicalSrcIdx = 78;
                    section.data(75).dtTransOffset = 74;

                    ;% rtP.IntegratorX_Oem_LowerSat
                    section.data(76).logicalSrcIdx = 79;
                    section.data(76).dtTransOffset = 75;

                    ;% rtP.Saturation_LowerSat_kzgxh2ssqh
                    section.data(77).logicalSrcIdx = 80;
                    section.data(77).dtTransOffset = 76;

                    ;% rtP.Saturation1_UpperSat_pjh2z4fnof
                    section.data(78).logicalSrcIdx = 81;
                    section.data(78).dtTransOffset = 77;

                    ;% rtP.Saturation1_LowerSat_o3inkji2se
                    section.data(79).logicalSrcIdx = 82;
                    section.data(79).dtTransOffset = 78;

                    ;% rtP.Gain2_Gain_jj2oxunwb2
                    section.data(80).logicalSrcIdx = 83;
                    section.data(80).dtTransOffset = 79;

                    ;% rtP.kmhms_Gain
                    section.data(81).logicalSrcIdx = 84;
                    section.data(81).dtTransOffset = 80;

                    ;% rtP.Constant21_Value
                    section.data(82).logicalSrcIdx = 85;
                    section.data(82).dtTransOffset = 81;

                    ;% rtP.Constant22_Value
                    section.data(83).logicalSrcIdx = 86;
                    section.data(83).dtTransOffset = 82;

                    ;% rtP.Constant23_Value
                    section.data(84).logicalSrcIdx = 87;
                    section.data(84).dtTransOffset = 83;

                    ;% rtP.Constant24_Value
                    section.data(85).logicalSrcIdx = 88;
                    section.data(85).dtTransOffset = 84;

                    ;% rtP.Constant25_Value
                    section.data(86).logicalSrcIdx = 89;
                    section.data(86).dtTransOffset = 85;

                    ;% rtP.Constant26_Value
                    section.data(87).logicalSrcIdx = 90;
                    section.data(87).dtTransOffset = 86;

                    ;% rtP.Constant27_Value
                    section.data(88).logicalSrcIdx = 91;
                    section.data(88).dtTransOffset = 87;

                    ;% rtP.Constant28_Value
                    section.data(89).logicalSrcIdx = 92;
                    section.data(89).dtTransOffset = 88;

                    ;% rtP.Constant29_Value
                    section.data(90).logicalSrcIdx = 93;
                    section.data(90).dtTransOffset = 89;

                    ;% rtP.Constant30_Value
                    section.data(91).logicalSrcIdx = 94;
                    section.data(91).dtTransOffset = 90;

                    ;% rtP.Constant32_Value
                    section.data(92).logicalSrcIdx = 95;
                    section.data(92).dtTransOffset = 91;

                    ;% rtP.Constant33_Value
                    section.data(93).logicalSrcIdx = 96;
                    section.data(93).dtTransOffset = 92;

                    ;% rtP.Constant34_Value
                    section.data(94).logicalSrcIdx = 97;
                    section.data(94).dtTransOffset = 93;

                    ;% rtP.Constant35_Value
                    section.data(95).logicalSrcIdx = 98;
                    section.data(95).dtTransOffset = 94;

                    ;% rtP.Constant36_Value
                    section.data(96).logicalSrcIdx = 99;
                    section.data(96).dtTransOffset = 95;

                    ;% rtP.Constant37_Value
                    section.data(97).logicalSrcIdx = 100;
                    section.data(97).dtTransOffset = 96;

                    ;% rtP.Constant38_Value
                    section.data(98).logicalSrcIdx = 101;
                    section.data(98).dtTransOffset = 97;

                    ;% rtP.Constant39_Value
                    section.data(99).logicalSrcIdx = 102;
                    section.data(99).dtTransOffset = 98;

                    ;% rtP.Gain11_Gain
                    section.data(100).logicalSrcIdx = 103;
                    section.data(100).dtTransOffset = 99;

                    ;% rtP.dummy3_Value
                    section.data(101).logicalSrcIdx = 104;
                    section.data(101).dtTransOffset = 100;

                    ;% rtP.Gain10_Gain
                    section.data(102).logicalSrcIdx = 105;
                    section.data(102).dtTransOffset = 101;

                    ;% rtP.dummy1_Value
                    section.data(103).logicalSrcIdx = 106;
                    section.data(103).dtTransOffset = 102;

                    ;% rtP.Gain7_Gain
                    section.data(104).logicalSrcIdx = 107;
                    section.data(104).dtTransOffset = 103;

                    ;% rtP.dummy2_Value
                    section.data(105).logicalSrcIdx = 108;
                    section.data(105).dtTransOffset = 104;

                    ;% rtP.const_Value
                    section.data(106).logicalSrcIdx = 109;
                    section.data(106).dtTransOffset = 105;

                    ;% rtP.Constant_Value_b5ccgfu4yk
                    section.data(107).logicalSrcIdx = 110;
                    section.data(107).dtTransOffset = 106;

                    ;% rtP.Constant_Value_nm5d5hyfni
                    section.data(108).logicalSrcIdx = 111;
                    section.data(108).dtTransOffset = 107;

                    ;% rtP.Constant2_Value
                    section.data(109).logicalSrcIdx = 112;
                    section.data(109).dtTransOffset = 108;

                    ;% rtP.Constant2_Value_c3vhbw33ec
                    section.data(110).logicalSrcIdx = 113;
                    section.data(110).dtTransOffset = 109;

                    ;% rtP.FuelLimit_Value
                    section.data(111).logicalSrcIdx = 114;
                    section.data(111).dtTransOffset = 110;

                    ;% rtP.Constant_Value_gcvl5az0p5
                    section.data(112).logicalSrcIdx = 115;
                    section.data(112).dtTransOffset = 111;

                    ;% rtP.Constant1_Value
                    section.data(113).logicalSrcIdx = 116;
                    section.data(113).dtTransOffset = 112;

                    ;% rtP.Constant1_Value_fe1czv4ovb
                    section.data(114).logicalSrcIdx = 117;
                    section.data(114).dtTransOffset = 113;

                    ;% rtP.Constant2_Value_imre1apqn2
                    section.data(115).logicalSrcIdx = 118;
                    section.data(115).dtTransOffset = 114;

                    ;% rtP.Constant1_Value_foo0ytc1ur
                    section.data(116).logicalSrcIdx = 119;
                    section.data(116).dtTransOffset = 115;

                    ;% rtP.Constant_Value_cfl4aorgnt
                    section.data(117).logicalSrcIdx = 120;
                    section.data(117).dtTransOffset = 116;

                    ;% rtP.Constant1_Value_kvscu5x5rd
                    section.data(118).logicalSrcIdx = 121;
                    section.data(118).dtTransOffset = 117;

                    ;% rtP.Constant2_Value_dfqgdtofyy
                    section.data(119).logicalSrcIdx = 122;
                    section.data(119).dtTransOffset = 118;

                    ;% rtP.Constant3_Value
                    section.data(120).logicalSrcIdx = 123;
                    section.data(120).dtTransOffset = 119;

                    ;% rtP.Constant_Value_dwh2dts0z5
                    section.data(121).logicalSrcIdx = 124;
                    section.data(121).dtTransOffset = 120;

                    ;% rtP.Constant_Value_pi0lofejm1
                    section.data(122).logicalSrcIdx = 125;
                    section.data(122).dtTransOffset = 121;

                    ;% rtP.Constant1_Value_cjbf34ugrc
                    section.data(123).logicalSrcIdx = 126;
                    section.data(123).dtTransOffset = 122;

                    ;% rtP.Constant_Value_ajsql1lpqg
                    section.data(124).logicalSrcIdx = 127;
                    section.data(124).dtTransOffset = 123;

            nTotData = nTotData + section.nData;
            paramMap.sections(5) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtP.StringConstant_String
                    section.data(1).logicalSrcIdx = 128;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.StringConstant1_String
                    section.data(2).logicalSrcIdx = 129;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            paramMap.sections(6) = section;
            clear section

            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% rtP.uDLookupTable_maxIndex
                    section.data(1).logicalSrcIdx = 130;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.uDLookupTable_dimSizes
                    section.data(2).logicalSrcIdx = 131;
                    section.data(2).dtTransOffset = 1;

                    ;% rtP.uDLookupTable_numYWorkElts
                    section.data(3).logicalSrcIdx = 132;
                    section.data(3).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            paramMap.sections(7) = section;
            clear section


            ;%
            ;% Non-auto Data (parameter)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        paramMap.nTotData = nTotData;



    ;%**************************
    ;% Create Block Output Map *
    ;%**************************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 5;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc sigMap
        ;%
        sigMap.nSections           = nTotSects;
        sigMap.sectIdxOffset       = sectIdxOffset;
            sigMap.sections(nTotSects) = dumSection; %prealloc
        sigMap.nTotData            = -1;

        ;%
        ;% Auto data (rtB)
        ;%
            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.pdpozm2pyi
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(1) = section;
            clear section

            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% rtB.hic4phvehd
                    section.data(1).logicalSrcIdx = 1;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.cua1wzatht
                    section.data(2).logicalSrcIdx = 2;
                    section.data(2).dtTransOffset = 1;

                    ;% rtB.fqxly0svox
                    section.data(3).logicalSrcIdx = 3;
                    section.data(3).dtTransOffset = 21;

            nTotData = nTotData + section.nData;
            sigMap.sections(2) = section;
            clear section

            section.nData     = 217;
            section.data(217)  = dumData; %prealloc

                    ;% rtB.fefmeddlto
                    section.data(1).logicalSrcIdx = 4;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.fegajgngwz
                    section.data(2).logicalSrcIdx = 5;
                    section.data(2).dtTransOffset = 1;

                    ;% rtB.bmo2rqwngx
                    section.data(3).logicalSrcIdx = 6;
                    section.data(3).dtTransOffset = 2;

                    ;% rtB.ejfqwmdcba
                    section.data(4).logicalSrcIdx = 7;
                    section.data(4).dtTransOffset = 3;

                    ;% rtB.cjmcjehzib
                    section.data(5).logicalSrcIdx = 8;
                    section.data(5).dtTransOffset = 4;

                    ;% rtB.lxhopxto0a
                    section.data(6).logicalSrcIdx = 9;
                    section.data(6).dtTransOffset = 5;

                    ;% rtB.iwgroxai2r
                    section.data(7).logicalSrcIdx = 10;
                    section.data(7).dtTransOffset = 6;

                    ;% rtB.mlhy3nfifs
                    section.data(8).logicalSrcIdx = 11;
                    section.data(8).dtTransOffset = 7;

                    ;% rtB.hplgmt4cua
                    section.data(9).logicalSrcIdx = 12;
                    section.data(9).dtTransOffset = 8;

                    ;% rtB.nvztpo42zx
                    section.data(10).logicalSrcIdx = 13;
                    section.data(10).dtTransOffset = 9;

                    ;% rtB.paqrt3aosc
                    section.data(11).logicalSrcIdx = 14;
                    section.data(11).dtTransOffset = 10;

                    ;% rtB.k13vzx0oza
                    section.data(12).logicalSrcIdx = 15;
                    section.data(12).dtTransOffset = 11;

                    ;% rtB.bwddlbipky
                    section.data(13).logicalSrcIdx = 16;
                    section.data(13).dtTransOffset = 12;

                    ;% rtB.j1c35nbnvo
                    section.data(14).logicalSrcIdx = 17;
                    section.data(14).dtTransOffset = 13;

                    ;% rtB.bt0yraf3qh
                    section.data(15).logicalSrcIdx = 18;
                    section.data(15).dtTransOffset = 14;

                    ;% rtB.lrkl1f4nyq
                    section.data(16).logicalSrcIdx = 19;
                    section.data(16).dtTransOffset = 15;

                    ;% rtB.fpsp5e4daw
                    section.data(17).logicalSrcIdx = 20;
                    section.data(17).dtTransOffset = 16;

                    ;% rtB.ooztqypzjf
                    section.data(18).logicalSrcIdx = 21;
                    section.data(18).dtTransOffset = 17;

                    ;% rtB.faymzhlev0
                    section.data(19).logicalSrcIdx = 22;
                    section.data(19).dtTransOffset = 18;

                    ;% rtB.gy11xlunmk
                    section.data(20).logicalSrcIdx = 23;
                    section.data(20).dtTransOffset = 19;

                    ;% rtB.o44mkznquh
                    section.data(21).logicalSrcIdx = 24;
                    section.data(21).dtTransOffset = 20;

                    ;% rtB.hjdh45uyy1
                    section.data(22).logicalSrcIdx = 25;
                    section.data(22).dtTransOffset = 21;

                    ;% rtB.cb4di0dti4
                    section.data(23).logicalSrcIdx = 26;
                    section.data(23).dtTransOffset = 22;

                    ;% rtB.klpxz3py2k
                    section.data(24).logicalSrcIdx = 27;
                    section.data(24).dtTransOffset = 23;

                    ;% rtB.dvczlbyjax
                    section.data(25).logicalSrcIdx = 28;
                    section.data(25).dtTransOffset = 24;

                    ;% rtB.bkoec5z0bm
                    section.data(26).logicalSrcIdx = 29;
                    section.data(26).dtTransOffset = 25;

                    ;% rtB.bfe1jqp3ql
                    section.data(27).logicalSrcIdx = 30;
                    section.data(27).dtTransOffset = 26;

                    ;% rtB.l2hnvs30zp
                    section.data(28).logicalSrcIdx = 31;
                    section.data(28).dtTransOffset = 27;

                    ;% rtB.cgnmu1btuu
                    section.data(29).logicalSrcIdx = 32;
                    section.data(29).dtTransOffset = 28;

                    ;% rtB.icjifd4a3j
                    section.data(30).logicalSrcIdx = 33;
                    section.data(30).dtTransOffset = 29;

                    ;% rtB.aur1x2p4r3
                    section.data(31).logicalSrcIdx = 34;
                    section.data(31).dtTransOffset = 30;

                    ;% rtB.lsjheazm1j
                    section.data(32).logicalSrcIdx = 35;
                    section.data(32).dtTransOffset = 31;

                    ;% rtB.efe3nojiks
                    section.data(33).logicalSrcIdx = 36;
                    section.data(33).dtTransOffset = 32;

                    ;% rtB.kifydbwdix
                    section.data(34).logicalSrcIdx = 37;
                    section.data(34).dtTransOffset = 33;

                    ;% rtB.lcaei1u3tp
                    section.data(35).logicalSrcIdx = 38;
                    section.data(35).dtTransOffset = 34;

                    ;% rtB.mkgmrqsz4m
                    section.data(36).logicalSrcIdx = 39;
                    section.data(36).dtTransOffset = 35;

                    ;% rtB.h3rgiaase1
                    section.data(37).logicalSrcIdx = 40;
                    section.data(37).dtTransOffset = 36;

                    ;% rtB.cumj2jjpd3
                    section.data(38).logicalSrcIdx = 41;
                    section.data(38).dtTransOffset = 37;

                    ;% rtB.omvi4tphx3
                    section.data(39).logicalSrcIdx = 42;
                    section.data(39).dtTransOffset = 38;

                    ;% rtB.gmmxsb1ncz
                    section.data(40).logicalSrcIdx = 43;
                    section.data(40).dtTransOffset = 39;

                    ;% rtB.anky1mhun4
                    section.data(41).logicalSrcIdx = 44;
                    section.data(41).dtTransOffset = 40;

                    ;% rtB.mko4spaqlt
                    section.data(42).logicalSrcIdx = 45;
                    section.data(42).dtTransOffset = 41;

                    ;% rtB.caa50ajekj
                    section.data(43).logicalSrcIdx = 46;
                    section.data(43).dtTransOffset = 42;

                    ;% rtB.pd4h1x0zka
                    section.data(44).logicalSrcIdx = 47;
                    section.data(44).dtTransOffset = 43;

                    ;% rtB.d33i42nznw
                    section.data(45).logicalSrcIdx = 48;
                    section.data(45).dtTransOffset = 44;

                    ;% rtB.hrozmhet10
                    section.data(46).logicalSrcIdx = 49;
                    section.data(46).dtTransOffset = 45;

                    ;% rtB.nnky4aaqaz
                    section.data(47).logicalSrcIdx = 50;
                    section.data(47).dtTransOffset = 46;

                    ;% rtB.kpnuhs4yan
                    section.data(48).logicalSrcIdx = 51;
                    section.data(48).dtTransOffset = 47;

                    ;% rtB.ai3npgqmd0
                    section.data(49).logicalSrcIdx = 52;
                    section.data(49).dtTransOffset = 48;

                    ;% rtB.c0cwgduetq
                    section.data(50).logicalSrcIdx = 53;
                    section.data(50).dtTransOffset = 49;

                    ;% rtB.kiwuycktce
                    section.data(51).logicalSrcIdx = 54;
                    section.data(51).dtTransOffset = 50;

                    ;% rtB.bdsfootlbo
                    section.data(52).logicalSrcIdx = 55;
                    section.data(52).dtTransOffset = 51;

                    ;% rtB.ig3aydedki
                    section.data(53).logicalSrcIdx = 56;
                    section.data(53).dtTransOffset = 52;

                    ;% rtB.egg3t2uoo3
                    section.data(54).logicalSrcIdx = 57;
                    section.data(54).dtTransOffset = 53;

                    ;% rtB.bahf0ftnyg
                    section.data(55).logicalSrcIdx = 58;
                    section.data(55).dtTransOffset = 54;

                    ;% rtB.mocnuvcpgp
                    section.data(56).logicalSrcIdx = 59;
                    section.data(56).dtTransOffset = 55;

                    ;% rtB.laxl1bi23g
                    section.data(57).logicalSrcIdx = 60;
                    section.data(57).dtTransOffset = 56;

                    ;% rtB.nyt5uikcfo
                    section.data(58).logicalSrcIdx = 61;
                    section.data(58).dtTransOffset = 57;

                    ;% rtB.ebhzjlfncx
                    section.data(59).logicalSrcIdx = 62;
                    section.data(59).dtTransOffset = 58;

                    ;% rtB.lsrw5owmej
                    section.data(60).logicalSrcIdx = 63;
                    section.data(60).dtTransOffset = 59;

                    ;% rtB.jdemdb52qn
                    section.data(61).logicalSrcIdx = 64;
                    section.data(61).dtTransOffset = 60;

                    ;% rtB.fzqijlk23t
                    section.data(62).logicalSrcIdx = 65;
                    section.data(62).dtTransOffset = 61;

                    ;% rtB.hmqeokdrxe
                    section.data(63).logicalSrcIdx = 66;
                    section.data(63).dtTransOffset = 62;

                    ;% rtB.paczzqkqdw
                    section.data(64).logicalSrcIdx = 67;
                    section.data(64).dtTransOffset = 63;

                    ;% rtB.kp3tvzs4pj
                    section.data(65).logicalSrcIdx = 68;
                    section.data(65).dtTransOffset = 64;

                    ;% rtB.pgdssncn1o
                    section.data(66).logicalSrcIdx = 69;
                    section.data(66).dtTransOffset = 65;

                    ;% rtB.hc01pdzof3
                    section.data(67).logicalSrcIdx = 70;
                    section.data(67).dtTransOffset = 66;

                    ;% rtB.gs1ggdpy4b
                    section.data(68).logicalSrcIdx = 71;
                    section.data(68).dtTransOffset = 67;

                    ;% rtB.gze5jcom5s
                    section.data(69).logicalSrcIdx = 72;
                    section.data(69).dtTransOffset = 68;

                    ;% rtB.ha4qtjrmin
                    section.data(70).logicalSrcIdx = 73;
                    section.data(70).dtTransOffset = 69;

                    ;% rtB.diwh55j5zr
                    section.data(71).logicalSrcIdx = 74;
                    section.data(71).dtTransOffset = 70;

                    ;% rtB.deirtazmpx
                    section.data(72).logicalSrcIdx = 75;
                    section.data(72).dtTransOffset = 71;

                    ;% rtB.hzphm3vuhc
                    section.data(73).logicalSrcIdx = 76;
                    section.data(73).dtTransOffset = 72;

                    ;% rtB.ddfsxk3pjm
                    section.data(74).logicalSrcIdx = 77;
                    section.data(74).dtTransOffset = 73;

                    ;% rtB.nxqvmomv1r
                    section.data(75).logicalSrcIdx = 78;
                    section.data(75).dtTransOffset = 74;

                    ;% rtB.pcmk2laltd
                    section.data(76).logicalSrcIdx = 79;
                    section.data(76).dtTransOffset = 75;

                    ;% rtB.ihfhxuyjzv
                    section.data(77).logicalSrcIdx = 80;
                    section.data(77).dtTransOffset = 76;

                    ;% rtB.cofo4dglob
                    section.data(78).logicalSrcIdx = 81;
                    section.data(78).dtTransOffset = 77;

                    ;% rtB.mtn4j2z4x0
                    section.data(79).logicalSrcIdx = 82;
                    section.data(79).dtTransOffset = 78;

                    ;% rtB.kaqpmomne3
                    section.data(80).logicalSrcIdx = 83;
                    section.data(80).dtTransOffset = 79;

                    ;% rtB.px4ho0kp5r
                    section.data(81).logicalSrcIdx = 84;
                    section.data(81).dtTransOffset = 80;

                    ;% rtB.fnlh0owg0m
                    section.data(82).logicalSrcIdx = 85;
                    section.data(82).dtTransOffset = 81;

                    ;% rtB.beztzub33z
                    section.data(83).logicalSrcIdx = 86;
                    section.data(83).dtTransOffset = 82;

                    ;% rtB.nvtq3ka1ru
                    section.data(84).logicalSrcIdx = 87;
                    section.data(84).dtTransOffset = 83;

                    ;% rtB.lx4vqnwa25
                    section.data(85).logicalSrcIdx = 88;
                    section.data(85).dtTransOffset = 84;

                    ;% rtB.hniruipvai
                    section.data(86).logicalSrcIdx = 89;
                    section.data(86).dtTransOffset = 85;

                    ;% rtB.aw3ze00r1f
                    section.data(87).logicalSrcIdx = 90;
                    section.data(87).dtTransOffset = 86;

                    ;% rtB.h1jzkaxeay
                    section.data(88).logicalSrcIdx = 91;
                    section.data(88).dtTransOffset = 87;

                    ;% rtB.et2uhmlji2
                    section.data(89).logicalSrcIdx = 92;
                    section.data(89).dtTransOffset = 88;

                    ;% rtB.fagi55uakt
                    section.data(90).logicalSrcIdx = 93;
                    section.data(90).dtTransOffset = 89;

                    ;% rtB.ds5nytnni5
                    section.data(91).logicalSrcIdx = 94;
                    section.data(91).dtTransOffset = 90;

                    ;% rtB.hr10hckzct
                    section.data(92).logicalSrcIdx = 95;
                    section.data(92).dtTransOffset = 91;

                    ;% rtB.kzvckvcpof
                    section.data(93).logicalSrcIdx = 96;
                    section.data(93).dtTransOffset = 92;

                    ;% rtB.fitzivdg3v
                    section.data(94).logicalSrcIdx = 97;
                    section.data(94).dtTransOffset = 93;

                    ;% rtB.njcgrc3zvm
                    section.data(95).logicalSrcIdx = 98;
                    section.data(95).dtTransOffset = 94;

                    ;% rtB.k5apsyzoda
                    section.data(96).logicalSrcIdx = 99;
                    section.data(96).dtTransOffset = 95;

                    ;% rtB.pgniezqsr0
                    section.data(97).logicalSrcIdx = 100;
                    section.data(97).dtTransOffset = 96;

                    ;% rtB.forqmcoyzl
                    section.data(98).logicalSrcIdx = 101;
                    section.data(98).dtTransOffset = 97;

                    ;% rtB.linntx1wlj
                    section.data(99).logicalSrcIdx = 102;
                    section.data(99).dtTransOffset = 98;

                    ;% rtB.eixkduik4f
                    section.data(100).logicalSrcIdx = 103;
                    section.data(100).dtTransOffset = 99;

                    ;% rtB.drzrfcyncc
                    section.data(101).logicalSrcIdx = 104;
                    section.data(101).dtTransOffset = 100;

                    ;% rtB.bvz3zvgshe
                    section.data(102).logicalSrcIdx = 105;
                    section.data(102).dtTransOffset = 101;

                    ;% rtB.jyisic03f3
                    section.data(103).logicalSrcIdx = 106;
                    section.data(103).dtTransOffset = 102;

                    ;% rtB.ogasawbx31
                    section.data(104).logicalSrcIdx = 107;
                    section.data(104).dtTransOffset = 103;

                    ;% rtB.otng3qjdpw
                    section.data(105).logicalSrcIdx = 108;
                    section.data(105).dtTransOffset = 104;

                    ;% rtB.ldefe4o41v
                    section.data(106).logicalSrcIdx = 109;
                    section.data(106).dtTransOffset = 105;

                    ;% rtB.ksirzoklu3
                    section.data(107).logicalSrcIdx = 110;
                    section.data(107).dtTransOffset = 106;

                    ;% rtB.j1zi0jrhi4
                    section.data(108).logicalSrcIdx = 111;
                    section.data(108).dtTransOffset = 107;

                    ;% rtB.ktvccmzbfr
                    section.data(109).logicalSrcIdx = 112;
                    section.data(109).dtTransOffset = 108;

                    ;% rtB.b4k3rvzg1m
                    section.data(110).logicalSrcIdx = 113;
                    section.data(110).dtTransOffset = 109;

                    ;% rtB.hotpdqr22m
                    section.data(111).logicalSrcIdx = 114;
                    section.data(111).dtTransOffset = 110;

                    ;% rtB.ky5hu1sl5r
                    section.data(112).logicalSrcIdx = 115;
                    section.data(112).dtTransOffset = 111;

                    ;% rtB.opyybpyray
                    section.data(113).logicalSrcIdx = 116;
                    section.data(113).dtTransOffset = 112;

                    ;% rtB.fp2bci2nfq
                    section.data(114).logicalSrcIdx = 117;
                    section.data(114).dtTransOffset = 113;

                    ;% rtB.f04oqjsfjx
                    section.data(115).logicalSrcIdx = 118;
                    section.data(115).dtTransOffset = 114;

                    ;% rtB.evvikftrhr
                    section.data(116).logicalSrcIdx = 119;
                    section.data(116).dtTransOffset = 115;

                    ;% rtB.ly5zsvwobo
                    section.data(117).logicalSrcIdx = 120;
                    section.data(117).dtTransOffset = 116;

                    ;% rtB.ibko4nml5o
                    section.data(118).logicalSrcIdx = 121;
                    section.data(118).dtTransOffset = 117;

                    ;% rtB.bbjwnzbysv
                    section.data(119).logicalSrcIdx = 122;
                    section.data(119).dtTransOffset = 118;

                    ;% rtB.k2q4u3lafs
                    section.data(120).logicalSrcIdx = 123;
                    section.data(120).dtTransOffset = 119;

                    ;% rtB.ay21w05qrx
                    section.data(121).logicalSrcIdx = 124;
                    section.data(121).dtTransOffset = 120;

                    ;% rtB.okv40fdgvu
                    section.data(122).logicalSrcIdx = 125;
                    section.data(122).dtTransOffset = 121;

                    ;% rtB.hwekqshicu
                    section.data(123).logicalSrcIdx = 126;
                    section.data(123).dtTransOffset = 122;

                    ;% rtB.omwgk4e1kl
                    section.data(124).logicalSrcIdx = 127;
                    section.data(124).dtTransOffset = 123;

                    ;% rtB.oeo3ys3ci4
                    section.data(125).logicalSrcIdx = 128;
                    section.data(125).dtTransOffset = 124;

                    ;% rtB.bk4hs1x304
                    section.data(126).logicalSrcIdx = 129;
                    section.data(126).dtTransOffset = 125;

                    ;% rtB.mvg3ssqh31
                    section.data(127).logicalSrcIdx = 130;
                    section.data(127).dtTransOffset = 126;

                    ;% rtB.dwqarhpyfj
                    section.data(128).logicalSrcIdx = 131;
                    section.data(128).dtTransOffset = 127;

                    ;% rtB.ouddd1bq5c
                    section.data(129).logicalSrcIdx = 132;
                    section.data(129).dtTransOffset = 128;

                    ;% rtB.iinqiuxn3i
                    section.data(130).logicalSrcIdx = 133;
                    section.data(130).dtTransOffset = 129;

                    ;% rtB.aiuwtukjl2
                    section.data(131).logicalSrcIdx = 134;
                    section.data(131).dtTransOffset = 130;

                    ;% rtB.jzkj5ctoqn
                    section.data(132).logicalSrcIdx = 135;
                    section.data(132).dtTransOffset = 131;

                    ;% rtB.p0pelhou1r
                    section.data(133).logicalSrcIdx = 136;
                    section.data(133).dtTransOffset = 132;

                    ;% rtB.jzm0xgagji
                    section.data(134).logicalSrcIdx = 137;
                    section.data(134).dtTransOffset = 133;

                    ;% rtB.ewquelfwcj
                    section.data(135).logicalSrcIdx = 138;
                    section.data(135).dtTransOffset = 134;

                    ;% rtB.pobigfdmnk
                    section.data(136).logicalSrcIdx = 139;
                    section.data(136).dtTransOffset = 135;

                    ;% rtB.mtgpjerup5
                    section.data(137).logicalSrcIdx = 140;
                    section.data(137).dtTransOffset = 136;

                    ;% rtB.iwb3403aih
                    section.data(138).logicalSrcIdx = 141;
                    section.data(138).dtTransOffset = 137;

                    ;% rtB.kny5u5cuyg
                    section.data(139).logicalSrcIdx = 142;
                    section.data(139).dtTransOffset = 138;

                    ;% rtB.pyprhl40ct
                    section.data(140).logicalSrcIdx = 143;
                    section.data(140).dtTransOffset = 139;

                    ;% rtB.n0czoqzhzp
                    section.data(141).logicalSrcIdx = 144;
                    section.data(141).dtTransOffset = 140;

                    ;% rtB.dcjlzvgjdk
                    section.data(142).logicalSrcIdx = 145;
                    section.data(142).dtTransOffset = 141;

                    ;% rtB.fwampsknte
                    section.data(143).logicalSrcIdx = 146;
                    section.data(143).dtTransOffset = 142;

                    ;% rtB.onmzapip3s
                    section.data(144).logicalSrcIdx = 147;
                    section.data(144).dtTransOffset = 143;

                    ;% rtB.k2xcyxwsbw
                    section.data(145).logicalSrcIdx = 148;
                    section.data(145).dtTransOffset = 144;

                    ;% rtB.l2ijibgtxt
                    section.data(146).logicalSrcIdx = 149;
                    section.data(146).dtTransOffset = 145;

                    ;% rtB.did2wrnqd3
                    section.data(147).logicalSrcIdx = 150;
                    section.data(147).dtTransOffset = 146;

                    ;% rtB.j51psxbbsa
                    section.data(148).logicalSrcIdx = 151;
                    section.data(148).dtTransOffset = 147;

                    ;% rtB.k5zbpv0nhl
                    section.data(149).logicalSrcIdx = 152;
                    section.data(149).dtTransOffset = 148;

                    ;% rtB.eqthr4105d
                    section.data(150).logicalSrcIdx = 153;
                    section.data(150).dtTransOffset = 149;

                    ;% rtB.ahq1w0grid
                    section.data(151).logicalSrcIdx = 154;
                    section.data(151).dtTransOffset = 150;

                    ;% rtB.orgilm5inb
                    section.data(152).logicalSrcIdx = 155;
                    section.data(152).dtTransOffset = 151;

                    ;% rtB.ojsnbdpor2
                    section.data(153).logicalSrcIdx = 156;
                    section.data(153).dtTransOffset = 152;

                    ;% rtB.nlmicoqsbz
                    section.data(154).logicalSrcIdx = 157;
                    section.data(154).dtTransOffset = 153;

                    ;% rtB.kntt0fbjnf
                    section.data(155).logicalSrcIdx = 158;
                    section.data(155).dtTransOffset = 154;

                    ;% rtB.os3kqcyax0
                    section.data(156).logicalSrcIdx = 159;
                    section.data(156).dtTransOffset = 155;

                    ;% rtB.jfjgbdkox2
                    section.data(157).logicalSrcIdx = 160;
                    section.data(157).dtTransOffset = 156;

                    ;% rtB.kbxdatlwxl
                    section.data(158).logicalSrcIdx = 161;
                    section.data(158).dtTransOffset = 157;

                    ;% rtB.ko0hu3j2c1
                    section.data(159).logicalSrcIdx = 162;
                    section.data(159).dtTransOffset = 158;

                    ;% rtB.niafhsfiuh
                    section.data(160).logicalSrcIdx = 163;
                    section.data(160).dtTransOffset = 159;

                    ;% rtB.denq2sx3ui
                    section.data(161).logicalSrcIdx = 164;
                    section.data(161).dtTransOffset = 160;

                    ;% rtB.iuxkrw4e5c
                    section.data(162).logicalSrcIdx = 165;
                    section.data(162).dtTransOffset = 161;

                    ;% rtB.fgov33fphh
                    section.data(163).logicalSrcIdx = 166;
                    section.data(163).dtTransOffset = 162;

                    ;% rtB.pzxkphoemf
                    section.data(164).logicalSrcIdx = 167;
                    section.data(164).dtTransOffset = 163;

                    ;% rtB.ivokndy15y
                    section.data(165).logicalSrcIdx = 168;
                    section.data(165).dtTransOffset = 164;

                    ;% rtB.kwjng0hwid
                    section.data(166).logicalSrcIdx = 169;
                    section.data(166).dtTransOffset = 165;

                    ;% rtB.obqy5rqktf
                    section.data(167).logicalSrcIdx = 170;
                    section.data(167).dtTransOffset = 166;

                    ;% rtB.dq2gexc5is
                    section.data(168).logicalSrcIdx = 171;
                    section.data(168).dtTransOffset = 167;

                    ;% rtB.j2u4yltrpp
                    section.data(169).logicalSrcIdx = 172;
                    section.data(169).dtTransOffset = 168;

                    ;% rtB.kyljpuifbw
                    section.data(170).logicalSrcIdx = 173;
                    section.data(170).dtTransOffset = 169;

                    ;% rtB.blszti35p5
                    section.data(171).logicalSrcIdx = 174;
                    section.data(171).dtTransOffset = 170;

                    ;% rtB.ja1ga1numg
                    section.data(172).logicalSrcIdx = 175;
                    section.data(172).dtTransOffset = 171;

                    ;% rtB.jx23xarepd
                    section.data(173).logicalSrcIdx = 176;
                    section.data(173).dtTransOffset = 172;

                    ;% rtB.gqm1fborqv
                    section.data(174).logicalSrcIdx = 177;
                    section.data(174).dtTransOffset = 173;

                    ;% rtB.oat5nwyvfb
                    section.data(175).logicalSrcIdx = 178;
                    section.data(175).dtTransOffset = 175;

                    ;% rtB.hmrufe3ypk
                    section.data(176).logicalSrcIdx = 179;
                    section.data(176).dtTransOffset = 177;

                    ;% rtB.dnrdowihpt
                    section.data(177).logicalSrcIdx = 180;
                    section.data(177).dtTransOffset = 179;

                    ;% rtB.hrhovrq2gk
                    section.data(178).logicalSrcIdx = 181;
                    section.data(178).dtTransOffset = 180;

                    ;% rtB.mqo4dyjf2d
                    section.data(179).logicalSrcIdx = 182;
                    section.data(179).dtTransOffset = 181;

                    ;% rtB.m0hw1e23zq
                    section.data(180).logicalSrcIdx = 183;
                    section.data(180).dtTransOffset = 182;

                    ;% rtB.llwhjyi5kh
                    section.data(181).logicalSrcIdx = 184;
                    section.data(181).dtTransOffset = 183;

                    ;% rtB.izbygssgku
                    section.data(182).logicalSrcIdx = 185;
                    section.data(182).dtTransOffset = 184;

                    ;% rtB.kadspyijan
                    section.data(183).logicalSrcIdx = 186;
                    section.data(183).dtTransOffset = 185;

                    ;% rtB.n5mu2ryb4f
                    section.data(184).logicalSrcIdx = 187;
                    section.data(184).dtTransOffset = 186;

                    ;% rtB.npvqij5mhv
                    section.data(185).logicalSrcIdx = 188;
                    section.data(185).dtTransOffset = 187;

                    ;% rtB.flepa2gomd
                    section.data(186).logicalSrcIdx = 189;
                    section.data(186).dtTransOffset = 188;

                    ;% rtB.cyuyr3knsa
                    section.data(187).logicalSrcIdx = 190;
                    section.data(187).dtTransOffset = 189;

                    ;% rtB.ig43bemqvs
                    section.data(188).logicalSrcIdx = 191;
                    section.data(188).dtTransOffset = 190;

                    ;% rtB.b1uoph40ee
                    section.data(189).logicalSrcIdx = 192;
                    section.data(189).dtTransOffset = 191;

                    ;% rtB.p1pmwhnw1j
                    section.data(190).logicalSrcIdx = 193;
                    section.data(190).dtTransOffset = 192;

                    ;% rtB.fn1q2rgqt1
                    section.data(191).logicalSrcIdx = 194;
                    section.data(191).dtTransOffset = 193;

                    ;% rtB.nawvezg5up
                    section.data(192).logicalSrcIdx = 195;
                    section.data(192).dtTransOffset = 194;

                    ;% rtB.ks5oubt5ho
                    section.data(193).logicalSrcIdx = 196;
                    section.data(193).dtTransOffset = 195;

                    ;% rtB.oahz3ap5xd
                    section.data(194).logicalSrcIdx = 197;
                    section.data(194).dtTransOffset = 196;

                    ;% rtB.egpw0yftwz
                    section.data(195).logicalSrcIdx = 198;
                    section.data(195).dtTransOffset = 197;

                    ;% rtB.lcmzvp5mvt
                    section.data(196).logicalSrcIdx = 199;
                    section.data(196).dtTransOffset = 198;

                    ;% rtB.ayyewbsw5d
                    section.data(197).logicalSrcIdx = 200;
                    section.data(197).dtTransOffset = 199;

                    ;% rtB.k4n1klhres
                    section.data(198).logicalSrcIdx = 201;
                    section.data(198).dtTransOffset = 200;

                    ;% rtB.fgbfua1b4j
                    section.data(199).logicalSrcIdx = 202;
                    section.data(199).dtTransOffset = 201;

                    ;% rtB.mms3wxyzqm
                    section.data(200).logicalSrcIdx = 203;
                    section.data(200).dtTransOffset = 202;

                    ;% rtB.abyfl0makg
                    section.data(201).logicalSrcIdx = 204;
                    section.data(201).dtTransOffset = 203;

                    ;% rtB.nmprwynq2w
                    section.data(202).logicalSrcIdx = 205;
                    section.data(202).dtTransOffset = 204;

                    ;% rtB.n0gg0eojnl
                    section.data(203).logicalSrcIdx = 206;
                    section.data(203).dtTransOffset = 205;

                    ;% rtB.gpuw4gaeyd
                    section.data(204).logicalSrcIdx = 207;
                    section.data(204).dtTransOffset = 206;

                    ;% rtB.dxjp03lei3
                    section.data(205).logicalSrcIdx = 208;
                    section.data(205).dtTransOffset = 207;

                    ;% rtB.mbcrayrbd0
                    section.data(206).logicalSrcIdx = 209;
                    section.data(206).dtTransOffset = 208;

                    ;% rtB.elz2or5t0r
                    section.data(207).logicalSrcIdx = 210;
                    section.data(207).dtTransOffset = 209;

                    ;% rtB.mb3bxfx2lb
                    section.data(208).logicalSrcIdx = 211;
                    section.data(208).dtTransOffset = 210;

                    ;% rtB.eq0q3y5jp5
                    section.data(209).logicalSrcIdx = 212;
                    section.data(209).dtTransOffset = 211;

                    ;% rtB.kc4ngec1x5
                    section.data(210).logicalSrcIdx = 213;
                    section.data(210).dtTransOffset = 212;

                    ;% rtB.d3yr0hfu1a
                    section.data(211).logicalSrcIdx = 214;
                    section.data(211).dtTransOffset = 213;

                    ;% rtB.j2q40ay2j1
                    section.data(212).logicalSrcIdx = 215;
                    section.data(212).dtTransOffset = 214;

                    ;% rtB.b0oj4tfbt4
                    section.data(213).logicalSrcIdx = 216;
                    section.data(213).dtTransOffset = 215;

                    ;% rtB.m1vu5h1j0f
                    section.data(214).logicalSrcIdx = 217;
                    section.data(214).dtTransOffset = 216;

                    ;% rtB.e10ply524g
                    section.data(215).logicalSrcIdx = 218;
                    section.data(215).dtTransOffset = 217;

                    ;% rtB.n22fqqxpxo
                    section.data(216).logicalSrcIdx = 220;
                    section.data(216).dtTransOffset = 218;

                    ;% rtB.ffstplvowd
                    section.data(217).logicalSrcIdx = 221;
                    section.data(217).dtTransOffset = 219;

            nTotData = nTotData + section.nData;
            sigMap.sections(3) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtB.kminp3y1kp
                    section.data(1).logicalSrcIdx = 222;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.fvm1pndj51
                    section.data(2).logicalSrcIdx = 223;
                    section.data(2).dtTransOffset = 31;

            nTotData = nTotData + section.nData;
            sigMap.sections(4) = section;
            clear section

            section.nData     = 19;
            section.data(19)  = dumData; %prealloc

                    ;% rtB.dtbeclhhb3
                    section.data(1).logicalSrcIdx = 224;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.l0kuu0ds13
                    section.data(2).logicalSrcIdx = 225;
                    section.data(2).dtTransOffset = 1;

                    ;% rtB.a33eudfoqk
                    section.data(3).logicalSrcIdx = 226;
                    section.data(3).dtTransOffset = 2;

                    ;% rtB.dn5b4tnvem
                    section.data(4).logicalSrcIdx = 227;
                    section.data(4).dtTransOffset = 3;

                    ;% rtB.bmptpxj5fu
                    section.data(5).logicalSrcIdx = 228;
                    section.data(5).dtTransOffset = 4;

                    ;% rtB.p5dhuulwqq
                    section.data(6).logicalSrcIdx = 229;
                    section.data(6).dtTransOffset = 5;

                    ;% rtB.dlya0nsoeh
                    section.data(7).logicalSrcIdx = 230;
                    section.data(7).dtTransOffset = 6;

                    ;% rtB.jro4altozu
                    section.data(8).logicalSrcIdx = 231;
                    section.data(8).dtTransOffset = 7;

                    ;% rtB.lq3cbmwulo
                    section.data(9).logicalSrcIdx = 232;
                    section.data(9).dtTransOffset = 8;

                    ;% rtB.d4bourvq1r
                    section.data(10).logicalSrcIdx = 233;
                    section.data(10).dtTransOffset = 9;

                    ;% rtB.eskiwmqp4i
                    section.data(11).logicalSrcIdx = 234;
                    section.data(11).dtTransOffset = 10;

                    ;% rtB.bajmf2pksh
                    section.data(12).logicalSrcIdx = 235;
                    section.data(12).dtTransOffset = 11;

                    ;% rtB.bk2poabk1f
                    section.data(13).logicalSrcIdx = 236;
                    section.data(13).dtTransOffset = 12;

                    ;% rtB.awfdpaljkk
                    section.data(14).logicalSrcIdx = 237;
                    section.data(14).dtTransOffset = 13;

                    ;% rtB.klnxngbb1k
                    section.data(15).logicalSrcIdx = 238;
                    section.data(15).dtTransOffset = 14;

                    ;% rtB.efkmx5vf54
                    section.data(16).logicalSrcIdx = 239;
                    section.data(16).dtTransOffset = 15;

                    ;% rtB.kvxbfpgjze
                    section.data(17).logicalSrcIdx = 240;
                    section.data(17).dtTransOffset = 16;

                    ;% rtB.d4fubsaq1v
                    section.data(18).logicalSrcIdx = 241;
                    section.data(18).dtTransOffset = 17;

                    ;% rtB.ooofdxrsnp
                    section.data(19).logicalSrcIdx = 242;
                    section.data(19).dtTransOffset = 18;

            nTotData = nTotData + section.nData;
            sigMap.sections(5) = section;
            clear section


            ;%
            ;% Non-auto Data (signal)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        sigMap.nTotData = nTotData;



    ;%*******************
    ;% Create DWork Map *
    ;%*******************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 10;
        sectIdxOffset = 5;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc dworkMap
        ;%
        dworkMap.nSections           = nTotSects;
        dworkMap.sectIdxOffset       = sectIdxOffset;
            dworkMap.sections(nTotSects) = dumSection; %prealloc
        dworkMap.nTotData            = -1;

        ;%
        ;% Auto data (rtDW)
        ;%
            section.nData     = 24;
            section.data(24)  = dumData; %prealloc

                    ;% rtDW.kpmtixcj35
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.mluvktfvfy
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.jtxmye3nth
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% rtDW.mp0kaoewzv
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% rtDW.l2wwwtxl4l
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

                    ;% rtDW.ox1qbuvuuc
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 5;

                    ;% rtDW.bffjy4cqw3
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 6;

                    ;% rtDW.omie0z5rtl
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 7;

                    ;% rtDW.ltzscgd5af
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 8;

                    ;% rtDW.iazakfnige
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 9;

                    ;% rtDW.b1sjehltlg
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 10;

                    ;% rtDW.hmg2uwdzcg
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 9915;

                    ;% rtDW.jahel4guj4
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 19820;

                    ;% rtDW.c1a2ddum24
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 19821;

                    ;% rtDW.h1t2m1slzp
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 19822;

                    ;% rtDW.jescywanqo
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 19823;

                    ;% rtDW.n3jvfqlh1d
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 19824;

                    ;% rtDW.jie24f0s0n
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 19825;

                    ;% rtDW.od5y3smrxh
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 19826;

                    ;% rtDW.bzxfv0jxlh
                    section.data(20).logicalSrcIdx = 19;
                    section.data(20).dtTransOffset = 19827;

                    ;% rtDW.ozxovagibo
                    section.data(21).logicalSrcIdx = 20;
                    section.data(21).dtTransOffset = 19828;

                    ;% rtDW.o0eadiapoc
                    section.data(22).logicalSrcIdx = 21;
                    section.data(22).dtTransOffset = 19829;

                    ;% rtDW.lgjsvdiy5a
                    section.data(23).logicalSrcIdx = 22;
                    section.data(23).dtTransOffset = 19830;

                    ;% rtDW.ozecqffs1t
                    section.data(24).logicalSrcIdx = 23;
                    section.data(24).dtTransOffset = 19967;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.ki10t4re5z
                    section.data(1).logicalSrcIdx = 24;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(2) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtDW.kgxadfuhgr.modelTStart
                    section.data(1).logicalSrcIdx = 25;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.ldxvb4zcz0.modelTStart
                    section.data(2).logicalSrcIdx = 26;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            dworkMap.sections(3) = section;
            clear section

            section.nData     = 122;
            section.data(122)  = dumData; %prealloc

                    ;% rtDW.ckmhctwgle.LoggedData
                    section.data(1).logicalSrcIdx = 27;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.jpjfz2svcl.CONFIGHANDLE
                    section.data(2).logicalSrcIdx = 28;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.kbixsgmskc.CONFIGHANDLE
                    section.data(3).logicalSrcIdx = 29;
                    section.data(3).dtTransOffset = 2;

                    ;% rtDW.maxcur2n31.NODEPTR
                    section.data(4).logicalSrcIdx = 30;
                    section.data(4).dtTransOffset = 3;

                    ;% rtDW.alvst5aflb.NODEPTR
                    section.data(5).logicalSrcIdx = 31;
                    section.data(5).dtTransOffset = 4;

                    ;% rtDW.iuixpdicwr.PGPTR
                    section.data(6).logicalSrcIdx = 32;
                    section.data(6).dtTransOffset = 5;

                    ;% rtDW.dlhpralghu.LoggedData
                    section.data(7).logicalSrcIdx = 33;
                    section.data(7).dtTransOffset = 6;

                    ;% rtDW.m4n4tlm3qw.LoggedData
                    section.data(8).logicalSrcIdx = 34;
                    section.data(8).dtTransOffset = 7;

                    ;% rtDW.kzspl1dppk.PGPTR
                    section.data(9).logicalSrcIdx = 35;
                    section.data(9).dtTransOffset = 11;

                    ;% rtDW.k2kbed5e0t.PGPTR
                    section.data(10).logicalSrcIdx = 36;
                    section.data(10).dtTransOffset = 12;

                    ;% rtDW.osuhy0wf15.PGPTR
                    section.data(11).logicalSrcIdx = 37;
                    section.data(11).dtTransOffset = 13;

                    ;% rtDW.clkxcrhgir.PGPTR
                    section.data(12).logicalSrcIdx = 38;
                    section.data(12).dtTransOffset = 14;

                    ;% rtDW.omjkcskvmm.LoggedData
                    section.data(13).logicalSrcIdx = 39;
                    section.data(13).dtTransOffset = 15;

                    ;% rtDW.e3hhsxef2w.PGPTR
                    section.data(14).logicalSrcIdx = 40;
                    section.data(14).dtTransOffset = 16;

                    ;% rtDW.of3rn5nxd4.PGPTR
                    section.data(15).logicalSrcIdx = 41;
                    section.data(15).dtTransOffset = 17;

                    ;% rtDW.bvdrbi2l1c.PGPTR
                    section.data(16).logicalSrcIdx = 42;
                    section.data(16).dtTransOffset = 18;

                    ;% rtDW.e3ktwiowkd.PGPTR
                    section.data(17).logicalSrcIdx = 43;
                    section.data(17).dtTransOffset = 19;

                    ;% rtDW.d4x2b0bhgu.PGPTR
                    section.data(18).logicalSrcIdx = 44;
                    section.data(18).dtTransOffset = 20;

                    ;% rtDW.krc0v3lfqy.PGPTR
                    section.data(19).logicalSrcIdx = 45;
                    section.data(19).dtTransOffset = 21;

                    ;% rtDW.kr1tkdktl0.PGPTR
                    section.data(20).logicalSrcIdx = 46;
                    section.data(20).dtTransOffset = 22;

                    ;% rtDW.imsyrbpl23.PGPTR
                    section.data(21).logicalSrcIdx = 47;
                    section.data(21).dtTransOffset = 23;

                    ;% rtDW.pwm5n5vpra.LoggedData
                    section.data(22).logicalSrcIdx = 48;
                    section.data(22).dtTransOffset = 24;

                    ;% rtDW.dwf1cmy2ra.LoggedData
                    section.data(23).logicalSrcIdx = 49;
                    section.data(23).dtTransOffset = 25;

                    ;% rtDW.gtasy1jsdx.AQHandles
                    section.data(24).logicalSrcIdx = 50;
                    section.data(24).dtTransOffset = 29;

                    ;% rtDW.ekxqe2lb2z.PGPTR
                    section.data(25).logicalSrcIdx = 51;
                    section.data(25).dtTransOffset = 30;

                    ;% rtDW.j2t1smeuiz
                    section.data(26).logicalSrcIdx = 52;
                    section.data(26).dtTransOffset = 31;

                    ;% rtDW.bd2sguzpuq
                    section.data(27).logicalSrcIdx = 53;
                    section.data(27).dtTransOffset = 32;

                    ;% rtDW.lqs2eqamfb
                    section.data(28).logicalSrcIdx = 54;
                    section.data(28).dtTransOffset = 38;

                    ;% rtDW.dp3k1dexua.LoggedData
                    section.data(29).logicalSrcIdx = 55;
                    section.data(29).dtTransOffset = 47;

                    ;% rtDW.btbog5aing.LoggedData
                    section.data(30).logicalSrcIdx = 56;
                    section.data(30).dtTransOffset = 48;

                    ;% rtDW.dsrqsv4lmb.LoggedData
                    section.data(31).logicalSrcIdx = 57;
                    section.data(31).dtTransOffset = 49;

                    ;% rtDW.acp0df3iba.LoggedData
                    section.data(32).logicalSrcIdx = 58;
                    section.data(32).dtTransOffset = 50;

                    ;% rtDW.p33krp3hyb.AQHandles
                    section.data(33).logicalSrcIdx = 59;
                    section.data(33).dtTransOffset = 51;

                    ;% rtDW.dzibnwkozv.AQHandles
                    section.data(34).logicalSrcIdx = 60;
                    section.data(34).dtTransOffset = 52;

                    ;% rtDW.m2ysthz4lp.AQHandles
                    section.data(35).logicalSrcIdx = 61;
                    section.data(35).dtTransOffset = 53;

                    ;% rtDW.ltc2bikvjk.AQHandles
                    section.data(36).logicalSrcIdx = 62;
                    section.data(36).dtTransOffset = 54;

                    ;% rtDW.fwhtblllbe.AQHandles
                    section.data(37).logicalSrcIdx = 63;
                    section.data(37).dtTransOffset = 55;

                    ;% rtDW.kyvzs2v1y5.AQHandles
                    section.data(38).logicalSrcIdx = 64;
                    section.data(38).dtTransOffset = 56;

                    ;% rtDW.a5wlo524la.AQHandles
                    section.data(39).logicalSrcIdx = 65;
                    section.data(39).dtTransOffset = 57;

                    ;% rtDW.osoqnotoxt.AQHandles
                    section.data(40).logicalSrcIdx = 66;
                    section.data(40).dtTransOffset = 58;

                    ;% rtDW.afai5j1n5f.AQHandles
                    section.data(41).logicalSrcIdx = 67;
                    section.data(41).dtTransOffset = 59;

                    ;% rtDW.gtasy1jsdxk.AQHandles
                    section.data(42).logicalSrcIdx = 68;
                    section.data(42).dtTransOffset = 60;

                    ;% rtDW.jtwmyt455q.AQHandles
                    section.data(43).logicalSrcIdx = 69;
                    section.data(43).dtTransOffset = 61;

                    ;% rtDW.k4tau4hadb.TUbufferPtrs
                    section.data(44).logicalSrcIdx = 70;
                    section.data(44).dtTransOffset = 62;

                    ;% rtDW.hku5cqszwy.TUbufferPtrs
                    section.data(45).logicalSrcIdx = 71;
                    section.data(45).dtTransOffset = 64;

                    ;% rtDW.fmunnl32cm.LoggedData
                    section.data(46).logicalSrcIdx = 72;
                    section.data(46).dtTransOffset = 66;

                    ;% rtDW.ikortawjg0.LoggedData
                    section.data(47).logicalSrcIdx = 73;
                    section.data(47).dtTransOffset = 67;

                    ;% rtDW.o0cbjrpiwk.AQHandles
                    section.data(48).logicalSrcIdx = 74;
                    section.data(48).dtTransOffset = 68;

                    ;% rtDW.dakk2fhtjk.AQHandles
                    section.data(49).logicalSrcIdx = 75;
                    section.data(49).dtTransOffset = 69;

                    ;% rtDW.nbxezyhs1i.LoggedData
                    section.data(50).logicalSrcIdx = 76;
                    section.data(50).dtTransOffset = 70;

                    ;% rtDW.bzrmj3zxqu.AQHandles
                    section.data(51).logicalSrcIdx = 77;
                    section.data(51).dtTransOffset = 71;

                    ;% rtDW.pudhr5q1sv.AQHandles
                    section.data(52).logicalSrcIdx = 78;
                    section.data(52).dtTransOffset = 72;

                    ;% rtDW.bp4u12rzh4.LoggedData
                    section.data(53).logicalSrcIdx = 79;
                    section.data(53).dtTransOffset = 73;

                    ;% rtDW.ahb0xajdg5.AQHandles
                    section.data(54).logicalSrcIdx = 80;
                    section.data(54).dtTransOffset = 74;

                    ;% rtDW.kfghz55atc.LoggedData
                    section.data(55).logicalSrcIdx = 81;
                    section.data(55).dtTransOffset = 75;

                    ;% rtDW.jj02cyrtix.AQHandles
                    section.data(56).logicalSrcIdx = 82;
                    section.data(56).dtTransOffset = 76;

                    ;% rtDW.dbvexqyya2.LoggedData
                    section.data(57).logicalSrcIdx = 83;
                    section.data(57).dtTransOffset = 77;

                    ;% rtDW.mduldnxlmb.AQHandles
                    section.data(58).logicalSrcIdx = 84;
                    section.data(58).dtTransOffset = 78;

                    ;% rtDW.oz0i0yjqqd.LoggedData
                    section.data(59).logicalSrcIdx = 85;
                    section.data(59).dtTransOffset = 79;

                    ;% rtDW.o2domeg4ik.AQHandles
                    section.data(60).logicalSrcIdx = 86;
                    section.data(60).dtTransOffset = 80;

                    ;% rtDW.jx0u12jtqd.LoggedData
                    section.data(61).logicalSrcIdx = 87;
                    section.data(61).dtTransOffset = 81;

                    ;% rtDW.gtasy1jsdxk2.AQHandles
                    section.data(62).logicalSrcIdx = 88;
                    section.data(62).dtTransOffset = 82;

                    ;% rtDW.pgtrfza33s.LoggedData
                    section.data(63).logicalSrcIdx = 89;
                    section.data(63).dtTransOffset = 83;

                    ;% rtDW.mhg3ukoydp.AQHandles
                    section.data(64).logicalSrcIdx = 90;
                    section.data(64).dtTransOffset = 84;

                    ;% rtDW.ov4way2tof.LoggedData
                    section.data(65).logicalSrcIdx = 91;
                    section.data(65).dtTransOffset = 85;

                    ;% rtDW.kqufha1qme.AQHandles
                    section.data(66).logicalSrcIdx = 92;
                    section.data(66).dtTransOffset = 86;

                    ;% rtDW.fidvncdjop.LoggedData
                    section.data(67).logicalSrcIdx = 93;
                    section.data(67).dtTransOffset = 87;

                    ;% rtDW.ck00fvktvl.AQHandles
                    section.data(68).logicalSrcIdx = 94;
                    section.data(68).dtTransOffset = 88;

                    ;% rtDW.d2de4uag14.LoggedData
                    section.data(69).logicalSrcIdx = 95;
                    section.data(69).dtTransOffset = 89;

                    ;% rtDW.fsc12ul0nq.AQHandles
                    section.data(70).logicalSrcIdx = 96;
                    section.data(70).dtTransOffset = 90;

                    ;% rtDW.n3hthjpxsy.LoggedData
                    section.data(71).logicalSrcIdx = 97;
                    section.data(71).dtTransOffset = 91;

                    ;% rtDW.jk5klgbkjx.AQHandles
                    section.data(72).logicalSrcIdx = 98;
                    section.data(72).dtTransOffset = 92;

                    ;% rtDW.n34n5fqe0k.LoggedData
                    section.data(73).logicalSrcIdx = 99;
                    section.data(73).dtTransOffset = 93;

                    ;% rtDW.bgmhbb2ggj.AQHandles
                    section.data(74).logicalSrcIdx = 100;
                    section.data(74).dtTransOffset = 94;

                    ;% rtDW.klqnmdizzb.LoggedData
                    section.data(75).logicalSrcIdx = 101;
                    section.data(75).dtTransOffset = 95;

                    ;% rtDW.jfed40pyro.AQHandles
                    section.data(76).logicalSrcIdx = 102;
                    section.data(76).dtTransOffset = 96;

                    ;% rtDW.a0fgq0yh1e.LoggedData
                    section.data(77).logicalSrcIdx = 103;
                    section.data(77).dtTransOffset = 97;

                    ;% rtDW.mgmkqdnd4h.AQHandles
                    section.data(78).logicalSrcIdx = 104;
                    section.data(78).dtTransOffset = 98;

                    ;% rtDW.lnn0v5njmk.LoggedData
                    section.data(79).logicalSrcIdx = 105;
                    section.data(79).dtTransOffset = 99;

                    ;% rtDW.cqmz0ka510.AQHandles
                    section.data(80).logicalSrcIdx = 106;
                    section.data(80).dtTransOffset = 100;

                    ;% rtDW.cotf1zhzxt.LoggedData
                    section.data(81).logicalSrcIdx = 107;
                    section.data(81).dtTransOffset = 101;

                    ;% rtDW.awm3x1p030.AQHandles
                    section.data(82).logicalSrcIdx = 108;
                    section.data(82).dtTransOffset = 102;

                    ;% rtDW.pz3v3lsswe.AQHandles
                    section.data(83).logicalSrcIdx = 109;
                    section.data(83).dtTransOffset = 103;

                    ;% rtDW.dnck3gwe1l.LoggedData
                    section.data(84).logicalSrcIdx = 110;
                    section.data(84).dtTransOffset = 104;

                    ;% rtDW.nji534mx2v.AQHandles
                    section.data(85).logicalSrcIdx = 111;
                    section.data(85).dtTransOffset = 105;

                    ;% rtDW.hk1cc0h0mo.LoggedData
                    section.data(86).logicalSrcIdx = 112;
                    section.data(86).dtTransOffset = 106;

                    ;% rtDW.kn50mamzgm.AQHandles
                    section.data(87).logicalSrcIdx = 113;
                    section.data(87).dtTransOffset = 107;

                    ;% rtDW.kptuczirt5.LoggedData
                    section.data(88).logicalSrcIdx = 114;
                    section.data(88).dtTransOffset = 108;

                    ;% rtDW.lz2njt4sro.AQHandles
                    section.data(89).logicalSrcIdx = 115;
                    section.data(89).dtTransOffset = 109;

                    ;% rtDW.eiuytjixgn.LoggedData
                    section.data(90).logicalSrcIdx = 116;
                    section.data(90).dtTransOffset = 110;

                    ;% rtDW.hw0crwwhgx.AQHandles
                    section.data(91).logicalSrcIdx = 117;
                    section.data(91).dtTransOffset = 111;

                    ;% rtDW.lg0y0ft0jg.LoggedData
                    section.data(92).logicalSrcIdx = 118;
                    section.data(92).dtTransOffset = 112;

                    ;% rtDW.odefyqi2dd.AQHandles
                    section.data(93).logicalSrcIdx = 119;
                    section.data(93).dtTransOffset = 113;

                    ;% rtDW.i2r5nvclht.LoggedData
                    section.data(94).logicalSrcIdx = 120;
                    section.data(94).dtTransOffset = 114;

                    ;% rtDW.jwv41mpadj.AQHandles
                    section.data(95).logicalSrcIdx = 121;
                    section.data(95).dtTransOffset = 115;

                    ;% rtDW.n0ff0fnxnz.LoggedData
                    section.data(96).logicalSrcIdx = 122;
                    section.data(96).dtTransOffset = 116;

                    ;% rtDW.mtia2gm3mn.AQHandles
                    section.data(97).logicalSrcIdx = 123;
                    section.data(97).dtTransOffset = 117;

                    ;% rtDW.k4x0ksvebo.LoggedData
                    section.data(98).logicalSrcIdx = 124;
                    section.data(98).dtTransOffset = 118;

                    ;% rtDW.acteg3xdu0.AQHandles
                    section.data(99).logicalSrcIdx = 125;
                    section.data(99).dtTransOffset = 119;

                    ;% rtDW.jkhls1x1xd.LoggedData
                    section.data(100).logicalSrcIdx = 126;
                    section.data(100).dtTransOffset = 120;

                    ;% rtDW.dd50e1xu1m.AQHandles
                    section.data(101).logicalSrcIdx = 127;
                    section.data(101).dtTransOffset = 121;

                    ;% rtDW.owv4g3fh0s.LoggedData
                    section.data(102).logicalSrcIdx = 128;
                    section.data(102).dtTransOffset = 122;

                    ;% rtDW.phol22yedf.AQHandles
                    section.data(103).logicalSrcIdx = 129;
                    section.data(103).dtTransOffset = 123;

                    ;% rtDW.mbaya5ksxj.LoggedData
                    section.data(104).logicalSrcIdx = 130;
                    section.data(104).dtTransOffset = 124;

                    ;% rtDW.pieup45y1d.AQHandles
                    section.data(105).logicalSrcIdx = 131;
                    section.data(105).dtTransOffset = 125;

                    ;% rtDW.o0pg4xxi5b.LoggedData
                    section.data(106).logicalSrcIdx = 132;
                    section.data(106).dtTransOffset = 126;

                    ;% rtDW.n4ipdfmwpg.AQHandles
                    section.data(107).logicalSrcIdx = 133;
                    section.data(107).dtTransOffset = 127;

                    ;% rtDW.h03ppf21vf.LoggedData
                    section.data(108).logicalSrcIdx = 134;
                    section.data(108).dtTransOffset = 128;

                    ;% rtDW.pp33uvzuj4.AQHandles
                    section.data(109).logicalSrcIdx = 135;
                    section.data(109).dtTransOffset = 129;

                    ;% rtDW.fdojmr2ecl.LoggedData
                    section.data(110).logicalSrcIdx = 136;
                    section.data(110).dtTransOffset = 130;

                    ;% rtDW.ap5xh2jdk5.LoggedData
                    section.data(111).logicalSrcIdx = 137;
                    section.data(111).dtTransOffset = 131;

                    ;% rtDW.kaiai5muqe.LoggedData
                    section.data(112).logicalSrcIdx = 138;
                    section.data(112).dtTransOffset = 132;

                    ;% rtDW.ii2sh4h1st.LoggedData
                    section.data(113).logicalSrcIdx = 139;
                    section.data(113).dtTransOffset = 133;

                    ;% rtDW.m51eciw0jw.LoggedData
                    section.data(114).logicalSrcIdx = 140;
                    section.data(114).dtTransOffset = 134;

                    ;% rtDW.awaialiapj.LoggedData
                    section.data(115).logicalSrcIdx = 141;
                    section.data(115).dtTransOffset = 135;

                    ;% rtDW.l41y0q41uv.LoggedData
                    section.data(116).logicalSrcIdx = 142;
                    section.data(116).dtTransOffset = 136;

                    ;% rtDW.f4etw2hcvw.LoggedData
                    section.data(117).logicalSrcIdx = 143;
                    section.data(117).dtTransOffset = 137;

                    ;% rtDW.bkhbnfm5sg.LoggedData
                    section.data(118).logicalSrcIdx = 144;
                    section.data(118).dtTransOffset = 138;

                    ;% rtDW.p4sflk0g2w.AQHandles
                    section.data(119).logicalSrcIdx = 145;
                    section.data(119).dtTransOffset = 139;

                    ;% rtDW.ofz4kqfoe0.AQHandles
                    section.data(120).logicalSrcIdx = 146;
                    section.data(120).dtTransOffset = 140;

                    ;% rtDW.pegf1lgc5k.CTLHandle
                    section.data(121).logicalSrcIdx = 147;
                    section.data(121).dtTransOffset = 141;

                    ;% rtDW.ft5nitf1xd.CTLHandle
                    section.data(122).logicalSrcIdx = 148;
                    section.data(122).dtTransOffset = 142;

            nTotData = nTotData + section.nData;
            dworkMap.sections(4) = section;
            clear section

            section.nData     = 7;
            section.data(7)  = dumData; %prealloc

                    ;% rtDW.imduqxhj3y
                    section.data(1).logicalSrcIdx = 149;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.h0ytymzc2i
                    section.data(2).logicalSrcIdx = 150;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.ndy1r3lteo
                    section.data(3).logicalSrcIdx = 151;
                    section.data(3).dtTransOffset = 2;

                    ;% rtDW.ono0qix5io
                    section.data(4).logicalSrcIdx = 152;
                    section.data(4).dtTransOffset = 3;

                    ;% rtDW.bih1twzowf
                    section.data(5).logicalSrcIdx = 153;
                    section.data(5).dtTransOffset = 4;

                    ;% rtDW.evb2jcnsmb
                    section.data(6).logicalSrcIdx = 154;
                    section.data(6).dtTransOffset = 5;

                    ;% rtDW.jcb0vgamw2
                    section.data(7).logicalSrcIdx = 155;
                    section.data(7).dtTransOffset = 6;

            nTotData = nTotData + section.nData;
            dworkMap.sections(5) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.g1tih4iurb
                    section.data(1).logicalSrcIdx = 156;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(6) = section;
            clear section

            section.nData     = 55;
            section.data(55)  = dumData; %prealloc

                    ;% rtDW.gk4tvjl5km.NODEADDR
                    section.data(1).logicalSrcIdx = 157;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.jqdnga4d0r.NODEADDR
                    section.data(2).logicalSrcIdx = 158;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.khs2ujrsdq
                    section.data(3).logicalSrcIdx = 159;
                    section.data(3).dtTransOffset = 2;

                    ;% rtDW.hoc4ujevyd
                    section.data(4).logicalSrcIdx = 160;
                    section.data(4).dtTransOffset = 3;

                    ;% rtDW.pqjv5ubgvq
                    section.data(5).logicalSrcIdx = 161;
                    section.data(5).dtTransOffset = 4;

                    ;% rtDW.dzwszeq5uo
                    section.data(6).logicalSrcIdx = 162;
                    section.data(6).dtTransOffset = 5;

                    ;% rtDW.lru3e1mvrz
                    section.data(7).logicalSrcIdx = 163;
                    section.data(7).dtTransOffset = 6;

                    ;% rtDW.luuegejdc0
                    section.data(8).logicalSrcIdx = 164;
                    section.data(8).dtTransOffset = 7;

                    ;% rtDW.nva3c2aiue
                    section.data(9).logicalSrcIdx = 165;
                    section.data(9).dtTransOffset = 8;

                    ;% rtDW.p1lgfwsxn3
                    section.data(10).logicalSrcIdx = 166;
                    section.data(10).dtTransOffset = 9;

                    ;% rtDW.ozura1lel3
                    section.data(11).logicalSrcIdx = 167;
                    section.data(11).dtTransOffset = 10;

                    ;% rtDW.cn5pwf5utq
                    section.data(12).logicalSrcIdx = 168;
                    section.data(12).dtTransOffset = 11;

                    ;% rtDW.c1d5q3vumy
                    section.data(13).logicalSrcIdx = 169;
                    section.data(13).dtTransOffset = 12;

                    ;% rtDW.flfjax3w0e
                    section.data(14).logicalSrcIdx = 170;
                    section.data(14).dtTransOffset = 13;

                    ;% rtDW.gluwhgdkil
                    section.data(15).logicalSrcIdx = 171;
                    section.data(15).dtTransOffset = 14;

                    ;% rtDW.onwpqbmdms
                    section.data(16).logicalSrcIdx = 172;
                    section.data(16).dtTransOffset = 15;

                    ;% rtDW.n0wxb1xzlc
                    section.data(17).logicalSrcIdx = 173;
                    section.data(17).dtTransOffset = 16;

                    ;% rtDW.mf4tzazbhp.Tail
                    section.data(18).logicalSrcIdx = 174;
                    section.data(18).dtTransOffset = 17;

                    ;% rtDW.pszwtqz0gn.Tail
                    section.data(19).logicalSrcIdx = 175;
                    section.data(19).dtTransOffset = 18;

                    ;% rtDW.dhwxr34two
                    section.data(20).logicalSrcIdx = 176;
                    section.data(20).dtTransOffset = 19;

                    ;% rtDW.bcl2uuqmhl
                    section.data(21).logicalSrcIdx = 177;
                    section.data(21).dtTransOffset = 20;

                    ;% rtDW.nxjlr5banb
                    section.data(22).logicalSrcIdx = 178;
                    section.data(22).dtTransOffset = 21;

                    ;% rtDW.ja1c4asgaz
                    section.data(23).logicalSrcIdx = 179;
                    section.data(23).dtTransOffset = 22;

                    ;% rtDW.btigisbrqf
                    section.data(24).logicalSrcIdx = 180;
                    section.data(24).dtTransOffset = 23;

                    ;% rtDW.ckyfoeqie5
                    section.data(25).logicalSrcIdx = 181;
                    section.data(25).dtTransOffset = 24;

                    ;% rtDW.ixaqaxatlt
                    section.data(26).logicalSrcIdx = 182;
                    section.data(26).dtTransOffset = 25;

                    ;% rtDW.fshou35ift
                    section.data(27).logicalSrcIdx = 183;
                    section.data(27).dtTransOffset = 26;

                    ;% rtDW.cflc32uwnd
                    section.data(28).logicalSrcIdx = 184;
                    section.data(28).dtTransOffset = 27;

                    ;% rtDW.oqko4zquza
                    section.data(29).logicalSrcIdx = 185;
                    section.data(29).dtTransOffset = 28;

                    ;% rtDW.h3mr0riybw
                    section.data(30).logicalSrcIdx = 186;
                    section.data(30).dtTransOffset = 29;

                    ;% rtDW.pfmhktgqz5
                    section.data(31).logicalSrcIdx = 187;
                    section.data(31).dtTransOffset = 30;

                    ;% rtDW.mquiy4fzeb
                    section.data(32).logicalSrcIdx = 188;
                    section.data(32).dtTransOffset = 31;

                    ;% rtDW.omeqzycfh2
                    section.data(33).logicalSrcIdx = 189;
                    section.data(33).dtTransOffset = 32;

                    ;% rtDW.imt2dcvft2
                    section.data(34).logicalSrcIdx = 190;
                    section.data(34).dtTransOffset = 33;

                    ;% rtDW.cwyukvwtwb
                    section.data(35).logicalSrcIdx = 191;
                    section.data(35).dtTransOffset = 34;

                    ;% rtDW.ipcifxvj5x
                    section.data(36).logicalSrcIdx = 192;
                    section.data(36).dtTransOffset = 35;

                    ;% rtDW.c2dyuklr3i
                    section.data(37).logicalSrcIdx = 193;
                    section.data(37).dtTransOffset = 36;

                    ;% rtDW.p40fsqbchl
                    section.data(38).logicalSrcIdx = 194;
                    section.data(38).dtTransOffset = 37;

                    ;% rtDW.l4mfodlgua
                    section.data(39).logicalSrcIdx = 195;
                    section.data(39).dtTransOffset = 38;

                    ;% rtDW.kf0zhsqe1e
                    section.data(40).logicalSrcIdx = 196;
                    section.data(40).dtTransOffset = 39;

                    ;% rtDW.ie2rbfy2dj
                    section.data(41).logicalSrcIdx = 197;
                    section.data(41).dtTransOffset = 40;

                    ;% rtDW.bi3ryeji3q
                    section.data(42).logicalSrcIdx = 198;
                    section.data(42).dtTransOffset = 41;

                    ;% rtDW.gexhlxucmx
                    section.data(43).logicalSrcIdx = 199;
                    section.data(43).dtTransOffset = 42;

                    ;% rtDW.bzymrve3xd
                    section.data(44).logicalSrcIdx = 200;
                    section.data(44).dtTransOffset = 43;

                    ;% rtDW.cjg2lxwx3p
                    section.data(45).logicalSrcIdx = 201;
                    section.data(45).dtTransOffset = 44;

                    ;% rtDW.jbxbvwznkw
                    section.data(46).logicalSrcIdx = 202;
                    section.data(46).dtTransOffset = 45;

                    ;% rtDW.ofeqpav0z1
                    section.data(47).logicalSrcIdx = 203;
                    section.data(47).dtTransOffset = 46;

                    ;% rtDW.f2rh3pjcf4
                    section.data(48).logicalSrcIdx = 204;
                    section.data(48).dtTransOffset = 47;

                    ;% rtDW.czpni4mnff
                    section.data(49).logicalSrcIdx = 205;
                    section.data(49).dtTransOffset = 48;

                    ;% rtDW.edzwglzc12
                    section.data(50).logicalSrcIdx = 206;
                    section.data(50).dtTransOffset = 49;

                    ;% rtDW.kcrt4gkpma
                    section.data(51).logicalSrcIdx = 207;
                    section.data(51).dtTransOffset = 50;

                    ;% rtDW.gdkaitdhn2
                    section.data(52).logicalSrcIdx = 208;
                    section.data(52).dtTransOffset = 51;

                    ;% rtDW.j4aiaaqlli
                    section.data(53).logicalSrcIdx = 209;
                    section.data(53).dtTransOffset = 52;

                    ;% rtDW.jw31kvp3ln
                    section.data(54).logicalSrcIdx = 210;
                    section.data(54).dtTransOffset = 53;

                    ;% rtDW.aetkdo2sks
                    section.data(55).logicalSrcIdx = 211;
                    section.data(55).dtTransOffset = 54;

            nTotData = nTotData + section.nData;
            dworkMap.sections(7) = section;
            clear section

            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% rtDW.dbfmnhxbxj
                    section.data(1).logicalSrcIdx = 212;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.p1nnlsrxke
                    section.data(2).logicalSrcIdx = 213;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.bfmr5zictt
                    section.data(3).logicalSrcIdx = 214;
                    section.data(3).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            dworkMap.sections(8) = section;
            clear section

            section.nData     = 6;
            section.data(6)  = dumData; %prealloc

                    ;% rtDW.nhh3pckv2z
                    section.data(1).logicalSrcIdx = 215;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.pu1q4zlmwb
                    section.data(2).logicalSrcIdx = 216;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.pe5pl50ynw
                    section.data(3).logicalSrcIdx = 217;
                    section.data(3).dtTransOffset = 2;

                    ;% rtDW.eda54vucfl
                    section.data(4).logicalSrcIdx = 218;
                    section.data(4).dtTransOffset = 3;

                    ;% rtDW.mnycq5gn5i
                    section.data(5).logicalSrcIdx = 219;
                    section.data(5).dtTransOffset = 4;

                    ;% rtDW.e4lgtlqce2
                    section.data(6).logicalSrcIdx = 220;
                    section.data(6).dtTransOffset = 5;

            nTotData = nTotData + section.nData;
            dworkMap.sections(9) = section;
            clear section

            section.nData     = 20;
            section.data(20)  = dumData; %prealloc

                    ;% rtDW.hpyvhbyyfk
                    section.data(1).logicalSrcIdx = 221;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.mv3mphax4f
                    section.data(2).logicalSrcIdx = 222;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.dyrzzohb5s
                    section.data(3).logicalSrcIdx = 223;
                    section.data(3).dtTransOffset = 2;

                    ;% rtDW.apmlxbmuwh
                    section.data(4).logicalSrcIdx = 224;
                    section.data(4).dtTransOffset = 3;

                    ;% rtDW.ogaaumd32e
                    section.data(5).logicalSrcIdx = 225;
                    section.data(5).dtTransOffset = 4;

                    ;% rtDW.gvkgxqsg5w
                    section.data(6).logicalSrcIdx = 226;
                    section.data(6).dtTransOffset = 5;

                    ;% rtDW.ksp31oyn4z
                    section.data(7).logicalSrcIdx = 227;
                    section.data(7).dtTransOffset = 6;

                    ;% rtDW.gwi2bo5yvs
                    section.data(8).logicalSrcIdx = 228;
                    section.data(8).dtTransOffset = 7;

                    ;% rtDW.dedzusgrw0
                    section.data(9).logicalSrcIdx = 229;
                    section.data(9).dtTransOffset = 8;

                    ;% rtDW.dqrx4b5l1l
                    section.data(10).logicalSrcIdx = 230;
                    section.data(10).dtTransOffset = 9;

                    ;% rtDW.ei55bolyl0
                    section.data(11).logicalSrcIdx = 231;
                    section.data(11).dtTransOffset = 10;

                    ;% rtDW.frdq0ezqxz
                    section.data(12).logicalSrcIdx = 232;
                    section.data(12).dtTransOffset = 11;

                    ;% rtDW.hc5kmkcx43
                    section.data(13).logicalSrcIdx = 233;
                    section.data(13).dtTransOffset = 12;

                    ;% rtDW.bp0lxwi25f
                    section.data(14).logicalSrcIdx = 234;
                    section.data(14).dtTransOffset = 13;

                    ;% rtDW.nd3tkuvjly
                    section.data(15).logicalSrcIdx = 235;
                    section.data(15).dtTransOffset = 14;

                    ;% rtDW.adrllpi2ax
                    section.data(16).logicalSrcIdx = 236;
                    section.data(16).dtTransOffset = 15;

                    ;% rtDW.cqvouu2ka3
                    section.data(17).logicalSrcIdx = 237;
                    section.data(17).dtTransOffset = 16;

                    ;% rtDW.j4h3zrlxtn
                    section.data(18).logicalSrcIdx = 238;
                    section.data(18).dtTransOffset = 17;

                    ;% rtDW.asj3qcjbaz
                    section.data(19).logicalSrcIdx = 239;
                    section.data(19).dtTransOffset = 18;

                    ;% rtDW.ok1wan2u4e
                    section.data(20).logicalSrcIdx = 240;
                    section.data(20).dtTransOffset = 19;

            nTotData = nTotData + section.nData;
            dworkMap.sections(10) = section;
            clear section


            ;%
            ;% Non-auto Data (dwork)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        dworkMap.nTotData = nTotData;



    ;%
    ;% Add individual maps to base struct.
    ;%

    targMap.paramMap  = paramMap;
    targMap.signalMap = sigMap;
    targMap.dworkMap  = dworkMap;

    ;%
    ;% Add checksums to base struct.
    ;%


    targMap.checksum0 = 2564456923;
    targMap.checksum1 = 14143646;
    targMap.checksum2 = 2799630258;
    targMap.checksum3 = 17045496;

