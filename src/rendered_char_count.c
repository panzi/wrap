#include "wrap.h"

// just something, probably not very correct
size_t rendered_char_count(const char *text, size_t len, size_t current_linelen, size_t tabwidth) {
    size_t count = 0;
    DECODE_UTF8(text, len, {
        if (codepoint == '\t') {
            count += tabwidth - ((current_linelen + count) % tabwidth);
            // count += 8; // XXX: not how tabs work
        } else if (codepoint >= ' ' && codepoint <= '~') {
            // ASCII fast path
            count += 1;
        } else if (
            // zero width stuff
            (codepoint <= 0x01DFF ?
                (codepoint <= 0x00D63 ?
                    (codepoint <= 0x00A02 ?
                        (codepoint <= 0x007F3 ?
                            (codepoint <= 0x0061A ?
                                (codepoint <= 0x005BD ?
                                    (codepoint <= 0x0009F ?
                                        (codepoint <= 0x0001F ?
                                            codepoint >= 0x00000 :
                                            (codepoint >= 0x0007F && codepoint <= 0x0009F)) :
                                        (codepoint <= 0x0036F ?
                                            codepoint >= 0x00300 :
                                            (codepoint <= 0x00487 ?
                                                codepoint >= 0x00483 :
                                                (codepoint >= 0x00591 && codepoint <= 0x005BD)))) :
                                    (codepoint <= 0x005C2 ?
                                        (codepoint == 0x005BF ||
                                            (codepoint >= 0x005C1 && codepoint <= 0x005C2)) :
                                        (codepoint <= 0x005C5 ?
                                            codepoint >= 0x005C4 :
                                            (codepoint == 0x005C7 ||
                                                (codepoint >= 0x00610 && codepoint <= 0x0061A))))) :
                                (codepoint <= 0x006E8 ?
                                    (codepoint <= 0x00670 ?
                                        (codepoint <= 0x0065F ?
                                            codepoint >= 0x0064B :
                                            codepoint == 0x00670) :
                                        (codepoint <= 0x006DC ?
                                            codepoint >= 0x006D6 :
                                            (codepoint <= 0x006E4 ?
                                                codepoint >= 0x006DF :
                                                (codepoint >= 0x006E7 && codepoint <= 0x006E8)))) :
                                    (codepoint <= 0x00711 ?
                                        (codepoint <= 0x006ED ?
                                            codepoint >= 0x006EA :
                                            codepoint == 0x00711) :
                                        (codepoint <= 0x0074A ?
                                            codepoint >= 0x00730 :
                                            (codepoint <= 0x007B0 ?
                                                codepoint >= 0x007A6 :
                                                (codepoint >= 0x007EB && codepoint <= 0x007F3)))))) :
                            (codepoint <= 0x0093C ?
                                (codepoint <= 0x0082D ?
                                    (codepoint <= 0x00819 ?
                                        (codepoint == 0x007FD ||
                                            (codepoint >= 0x00816 && codepoint <= 0x00819)) :
                                        (codepoint <= 0x00823 ?
                                            codepoint >= 0x0081B :
                                            (codepoint <= 0x00827 ?
                                                codepoint >= 0x00825 :
                                                (codepoint >= 0x00829 && codepoint <= 0x0082D)))) :
                                    (codepoint <= 0x008E1 ?
                                        (codepoint <= 0x0085B ?
                                            codepoint >= 0x00859 :
                                            (codepoint >= 0x008D3 && codepoint <= 0x008E1)) :
                                        (codepoint <= 0x00902 ?
                                            codepoint >= 0x008E3 :
                                            (codepoint == 0x0093A ||
                                                codepoint == 0x0093C)))) :
                                (codepoint <= 0x00981 ?
                                    (codepoint <= 0x0094D ?
                                        (codepoint <= 0x00948 ?
                                            codepoint >= 0x00941 :
                                            codepoint == 0x0094D) :
                                        (codepoint <= 0x00957 ?
                                            codepoint >= 0x00951 :
                                            (codepoint <= 0x00963 ?
                                                codepoint >= 0x00962 :
                                                codepoint == 0x00981))) :
                                    (codepoint <= 0x009CD ?
                                        (codepoint == 0x009BC ||
                                            (codepoint <= 0x009C4 ?
                                                codepoint >= 0x009C1 :
                                                codepoint == 0x009CD)) :
                                        (codepoint <= 0x009E3 ?
                                            codepoint >= 0x009E2 :
                                            (codepoint == 0x009FE ||
                                                (codepoint >= 0x00A01 && codepoint <= 0x00A02))))))) :
                        (codepoint <= 0x00B63 ?
                            (codepoint <= 0x00AC5 ?
                                (codepoint <= 0x00A51 ?
                                    (codepoint <= 0x00A42 ?
                                        (codepoint == 0x00A3C ||
                                            (codepoint >= 0x00A41 && codepoint <= 0x00A42)) :
                                        (codepoint <= 0x00A48 ?
                                            codepoint >= 0x00A47 :
                                            (codepoint <= 0x00A4D ?
                                                codepoint >= 0x00A4B :
                                                codepoint == 0x00A51))) :
                                    (codepoint <= 0x00A75 ?
                                        (codepoint <= 0x00A71 ?
                                            codepoint >= 0x00A70 :
                                            codepoint == 0x00A75) :
                                        (codepoint <= 0x00A82 ?
                                            codepoint >= 0x00A81 :
                                            (codepoint == 0x00ABC ||
                                                (codepoint >= 0x00AC1 && codepoint <= 0x00AC5))))) :
                                (codepoint <= 0x00B01 ?
                                    (codepoint <= 0x00ACD ?
                                        (codepoint <= 0x00AC8 ?
                                            codepoint >= 0x00AC7 :
                                            codepoint == 0x00ACD) :
                                        (codepoint <= 0x00AE3 ?
                                            codepoint >= 0x00AE2 :
                                            (codepoint <= 0x00AFF ?
                                                codepoint >= 0x00AFA :
                                                codepoint == 0x00B01))) :
                                    (codepoint <= 0x00B44 ?
                                        (codepoint == 0x00B3C ||
                                            (codepoint == 0x00B3F ||
                                                (codepoint >= 0x00B41 && codepoint <= 0x00B44))) :
                                        (codepoint == 0x00B4D ||
                                            (codepoint <= 0x00B56 ?
                                                codepoint >= 0x00B55 :
                                                (codepoint >= 0x00B62 && codepoint <= 0x00B63)))))) :
                            (codepoint <= 0x00C63 ?
                                (codepoint <= 0x00C04 ?
                                    (codepoint <= 0x00BC0 ?
                                        (codepoint == 0x00B82 ||
                                            codepoint == 0x00BC0) :
                                        (codepoint == 0x00BCD ||
                                            (codepoint == 0x00C00 ||
                                                codepoint == 0x00C04))) :
                                    (codepoint <= 0x00C48 ?
                                        (codepoint <= 0x00C40 ?
                                            codepoint >= 0x00C3E :
                                            (codepoint >= 0x00C46 && codepoint <= 0x00C48)) :
                                        (codepoint <= 0x00C4D ?
                                            codepoint >= 0x00C4A :
                                            (codepoint <= 0x00C56 ?
                                                codepoint >= 0x00C55 :
                                                (codepoint >= 0x00C62 && codepoint <= 0x00C63))))) :
                                (codepoint <= 0x00CCD ?
                                    (codepoint <= 0x00CBC ?
                                        (codepoint == 0x00C81 ||
                                            codepoint == 0x00CBC) :
                                        (codepoint == 0x00CBF ||
                                            (codepoint == 0x00CC6 ||
                                                (codepoint >= 0x00CCC && codepoint <= 0x00CCD)))) :
                                    (codepoint <= 0x00D3C ?
                                        (codepoint <= 0x00CE3 ?
                                            codepoint >= 0x00CE2 :
                                            (codepoint <= 0x00D01 ?
                                                codepoint >= 0x00D00 :
                                                (codepoint >= 0x00D3B && codepoint <= 0x00D3C))) :
                                        (codepoint <= 0x00D44 ?
                                            codepoint >= 0x00D41 :
                                            (codepoint == 0x00D4D ||
                                                (codepoint >= 0x00D62 && codepoint <= 0x00D63)))))))) :
                    (codepoint <= 0x017DD ?
                        (codepoint <= 0x00FC6 ?
                            (codepoint <= 0x00ECD ?
                                (codepoint <= 0x00E31 ?
                                    (codepoint <= 0x00DCA ?
                                        (codepoint == 0x00D81 ||
                                            codepoint == 0x00DCA) :
                                        (codepoint <= 0x00DD4 ?
                                            codepoint >= 0x00DD2 :
                                            (codepoint == 0x00DD6 ||
                                                codepoint == 0x00E31))) :
                                    (codepoint <= 0x00E4E ?
                                        (codepoint <= 0x00E3A ?
                                            codepoint >= 0x00E34 :
                                            (codepoint >= 0x00E47 && codepoint <= 0x00E4E)) :
                                        (codepoint == 0x00EB1 ||
                                            (codepoint <= 0x00EBC ?
                                                codepoint >= 0x00EB4 :
                                                (codepoint >= 0x00EC8 && codepoint <= 0x00ECD))))) :
                                (codepoint <= 0x00F7E ?
                                    (codepoint <= 0x00F35 ?
                                        (codepoint <= 0x00F19 ?
                                            codepoint >= 0x00F18 :
                                            codepoint == 0x00F35) :
                                        (codepoint == 0x00F37 ||
                                            (codepoint == 0x00F39 ||
                                                (codepoint >= 0x00F71 && codepoint <= 0x00F7E)))) :
                                    (codepoint <= 0x00F87 ?
                                        (codepoint <= 0x00F84 ?
                                            codepoint >= 0x00F80 :
                                            (codepoint >= 0x00F86 && codepoint <= 0x00F87)) :
                                        (codepoint <= 0x00F97 ?
                                            codepoint >= 0x00F8D :
                                            (codepoint <= 0x00FBC ?
                                                codepoint >= 0x00F99 :
                                                codepoint == 0x00FC6))))) :
                            (codepoint <= 0x0108D ?
                                (codepoint <= 0x01059 ?
                                    (codepoint <= 0x01037 ?
                                        (codepoint <= 0x01030 ?
                                            codepoint >= 0x0102D :
                                            (codepoint >= 0x01032 && codepoint <= 0x01037)) :
                                        (codepoint <= 0x0103A ?
                                            codepoint >= 0x01039 :
                                            (codepoint <= 0x0103E ?
                                                codepoint >= 0x0103D :
                                                (codepoint >= 0x01058 && codepoint <= 0x01059)))) :
                                    (codepoint <= 0x01074 ?
                                        (codepoint <= 0x01060 ?
                                            codepoint >= 0x0105E :
                                            (codepoint >= 0x01071 && codepoint <= 0x01074)) :
                                        (codepoint == 0x01082 ||
                                            (codepoint <= 0x01086 ?
                                                codepoint >= 0x01085 :
                                                codepoint == 0x0108D)))) :
                                (codepoint <= 0x01753 ?
                                    (codepoint <= 0x0135F ?
                                        (codepoint == 0x0109D ||
                                            (codepoint >= 0x0135D && codepoint <= 0x0135F)) :
                                        (codepoint <= 0x01714 ?
                                            codepoint >= 0x01712 :
                                            (codepoint <= 0x01734 ?
                                                codepoint >= 0x01732 :
                                                (codepoint >= 0x01752 && codepoint <= 0x01753)))) :
                                    (codepoint <= 0x017BD ?
                                        (codepoint <= 0x01773 ?
                                            codepoint >= 0x01772 :
                                            (codepoint <= 0x017B5 ?
                                                codepoint >= 0x017B4 :
                                                (codepoint >= 0x017B7 && codepoint <= 0x017BD))) :
                                        (codepoint == 0x017C6 ||
                                            (codepoint <= 0x017D3 ?
                                                codepoint >= 0x017C9 :
                                                codepoint == 0x017DD)))))) :
                        (codepoint <= 0x01B3A ?
                            (codepoint <= 0x01A56 ?
                                (codepoint <= 0x01928 ?
                                    (codepoint <= 0x01886 ?
                                        (codepoint <= 0x0180D ?
                                            codepoint >= 0x0180B :
                                            (codepoint >= 0x01885 && codepoint <= 0x01886)) :
                                        (codepoint == 0x018A9 ||
                                            (codepoint <= 0x01922 ?
                                                codepoint >= 0x01920 :
                                                (codepoint >= 0x01927 && codepoint <= 0x01928)))) :
                                    (codepoint <= 0x0193B ?
                                        (codepoint == 0x01932 ||
                                            (codepoint >= 0x01939 && codepoint <= 0x0193B)) :
                                        (codepoint <= 0x01A18 ?
                                            codepoint >= 0x01A17 :
                                            (codepoint == 0x01A1B ||
                                                codepoint == 0x01A56)))) :
                                (codepoint <= 0x01A7C ?
                                    (codepoint <= 0x01A60 ?
                                        (codepoint <= 0x01A5E ?
                                            codepoint >= 0x01A58 :
                                            codepoint == 0x01A60) :
                                        (codepoint == 0x01A62 ||
                                            (codepoint <= 0x01A6C ?
                                                codepoint >= 0x01A65 :
                                                (codepoint >= 0x01A73 && codepoint <= 0x01A7C)))) :
                                    (codepoint <= 0x01AC0 ?
                                        (codepoint == 0x01A7F ||
                                            (codepoint <= 0x01ABD ?
                                                codepoint >= 0x01AB0 :
                                                (codepoint >= 0x01ABF && codepoint <= 0x01AC0))) :
                                        (codepoint <= 0x01B03 ?
                                            codepoint >= 0x01B00 :
                                            (codepoint == 0x01B34 ||
                                                (codepoint >= 0x01B36 && codepoint <= 0x01B3A)))))) :
                            (codepoint <= 0x01BED ?
                                (codepoint <= 0x01BA5 ?
                                    (codepoint <= 0x01B42 ?
                                        (codepoint == 0x01B3C ||
                                            codepoint == 0x01B42) :
                                        (codepoint <= 0x01B73 ?
                                            codepoint >= 0x01B6B :
                                            (codepoint <= 0x01B81 ?
                                                codepoint >= 0x01B80 :
                                                (codepoint >= 0x01BA2 && codepoint <= 0x01BA5)))) :
                                    (codepoint <= 0x01BAD ?
                                        (codepoint <= 0x01BA9 ?
                                            codepoint >= 0x01BA8 :
                                            (codepoint >= 0x01BAB && codepoint <= 0x01BAD)) :
                                        (codepoint == 0x01BE6 ||
                                            (codepoint <= 0x01BE9 ?
                                                codepoint >= 0x01BE8 :
                                                codepoint == 0x01BED)))) :
                                (codepoint <= 0x01CE0 ?
                                    (codepoint <= 0x01C33 ?
                                        (codepoint <= 0x01BF1 ?
                                            codepoint >= 0x01BEF :
                                            (codepoint >= 0x01C2C && codepoint <= 0x01C33)) :
                                        (codepoint <= 0x01C37 ?
                                            codepoint >= 0x01C36 :
                                            (codepoint <= 0x01CD2 ?
                                                codepoint >= 0x01CD0 :
                                                (codepoint >= 0x01CD4 && codepoint <= 0x01CE0)))) :
                                    (codepoint <= 0x01CF4 ?
                                        (codepoint <= 0x01CE8 ?
                                            codepoint >= 0x01CE2 :
                                            (codepoint == 0x01CED ||
                                                codepoint == 0x01CF4)) :
                                        (codepoint <= 0x01CF9 ?
                                            codepoint >= 0x01CF8 :
                                            (codepoint <= 0x01DF9 ?
                                                codepoint >= 0x01DC0 :
                                                (codepoint >= 0x01DFB && codepoint <= 0x01DFF))))))))) :
                (codepoint <= 0x1136C ?
                    (codepoint <= 0x0AAF6 ?
                        (codepoint <= 0x0A8F1 ?
                            (codepoint <= 0x0A66F ?
                                (codepoint <= 0x02CF1 ?
                                    (codepoint <= 0x020DC ?
                                        (codepoint <= 0x0200F ?
                                            codepoint >= 0x0200B :
                                            (codepoint >= 0x020D0 && codepoint <= 0x020DC)) :
                                        (codepoint == 0x020E1 ||
                                            (codepoint <= 0x020F0 ?
                                                codepoint >= 0x020E5 :
                                                (codepoint >= 0x02CEF && codepoint <= 0x02CF1)))) :
                                    (codepoint <= 0x02DFF ?
                                        (codepoint == 0x02D7F ||
                                            (codepoint >= 0x02DE0 && codepoint <= 0x02DFF)) :
                                        (codepoint <= 0x0302D ?
                                            codepoint >= 0x0302A :
                                            (codepoint <= 0x0309A ?
                                                codepoint >= 0x03099 :
                                                codepoint == 0x0A66F)))) :
                                (codepoint <= 0x0A806 ?
                                    (codepoint <= 0x0A69F ?
                                        (codepoint <= 0x0A67D ?
                                            codepoint >= 0x0A674 :
                                            (codepoint >= 0x0A69E && codepoint <= 0x0A69F)) :
                                        (codepoint <= 0x0A6F1 ?
                                            codepoint >= 0x0A6F0 :
                                            (codepoint == 0x0A802 ||
                                                codepoint == 0x0A806))) :
                                    (codepoint <= 0x0A826 ?
                                        (codepoint == 0x0A80B ||
                                            (codepoint >= 0x0A825 && codepoint <= 0x0A826)) :
                                        (codepoint == 0x0A82C ||
                                            (codepoint <= 0x0A8C5 ?
                                                codepoint >= 0x0A8C4 :
                                                (codepoint >= 0x0A8E0 && codepoint <= 0x0A8F1)))))) :
                            (codepoint <= 0x0AA32 ?
                                (codepoint <= 0x0A9B3 ?
                                    (codepoint <= 0x0A92D ?
                                        (codepoint == 0x0A8FF ||
                                            (codepoint >= 0x0A926 && codepoint <= 0x0A92D)) :
                                        (codepoint <= 0x0A951 ?
                                            codepoint >= 0x0A947 :
                                            (codepoint <= 0x0A982 ?
                                                codepoint >= 0x0A980 :
                                                codepoint == 0x0A9B3))) :
                                    (codepoint <= 0x0A9BD ?
                                        (codepoint <= 0x0A9B9 ?
                                            codepoint >= 0x0A9B6 :
                                            (codepoint >= 0x0A9BC && codepoint <= 0x0A9BD)) :
                                        (codepoint == 0x0A9E5 ||
                                            (codepoint <= 0x0AA2E ?
                                                codepoint >= 0x0AA29 :
                                                (codepoint >= 0x0AA31 && codepoint <= 0x0AA32))))) :
                                (codepoint <= 0x0AAB0 ?
                                    (codepoint <= 0x0AA43 ?
                                        (codepoint <= 0x0AA36 ?
                                            codepoint >= 0x0AA35 :
                                            codepoint == 0x0AA43) :
                                        (codepoint == 0x0AA4C ||
                                            (codepoint == 0x0AA7C ||
                                                codepoint == 0x0AAB0))) :
                                    (codepoint <= 0x0AABF ?
                                        (codepoint <= 0x0AAB4 ?
                                            codepoint >= 0x0AAB2 :
                                            (codepoint <= 0x0AAB8 ?
                                                codepoint >= 0x0AAB7 :
                                                (codepoint >= 0x0AABE && codepoint <= 0x0AABF))) :
                                        (codepoint == 0x0AAC1 ||
                                            (codepoint <= 0x0AAED ?
                                                codepoint >= 0x0AAEC :
                                                codepoint == 0x0AAF6)))))) :
                        (codepoint <= 0x11046 ?
                            (codepoint <= 0x1037A ?
                                (codepoint <= 0x0FE0F ?
                                    (codepoint <= 0x0ABE8 ?
                                        (codepoint == 0x0ABE5 ||
                                            codepoint == 0x0ABE8) :
                                        (codepoint == 0x0ABED ||
                                            (codepoint == 0x0FB1E ||
                                                (codepoint >= 0x0FE00 && codepoint <= 0x0FE0F)))) :
                                    (codepoint <= 0x0FE2F ?
                                        (codepoint <= 0x0FE0F ?
                                            codepoint >= 0x0FE00 :
                                            (codepoint >= 0x0FE20 && codepoint <= 0x0FE2F)) :
                                        (codepoint == 0x101FD ||
                                            (codepoint == 0x102E0 ||
                                                (codepoint >= 0x10376 && codepoint <= 0x1037A))))) :
                                (codepoint <= 0x10A3F ?
                                    (codepoint <= 0x10A06 ?
                                        (codepoint <= 0x10A03 ?
                                            codepoint >= 0x10A01 :
                                            (codepoint >= 0x10A05 && codepoint <= 0x10A06)) :
                                        (codepoint <= 0x10A0F ?
                                            codepoint >= 0x10A0C :
                                            (codepoint <= 0x10A3A ?
                                                codepoint >= 0x10A38 :
                                                codepoint == 0x10A3F))) :
                                    (codepoint <= 0x10EAC ?
                                        (codepoint <= 0x10AE6 ?
                                            codepoint >= 0x10AE5 :
                                            (codepoint <= 0x10D27 ?
                                                codepoint >= 0x10D24 :
                                                (codepoint >= 0x10EAB && codepoint <= 0x10EAC))) :
                                        (codepoint <= 0x10F50 ?
                                            codepoint >= 0x10F46 :
                                            (codepoint == 0x11001 ||
                                                (codepoint >= 0x11038 && codepoint <= 0x11046)))))) :
                            (codepoint <= 0x111CC ?
                                (codepoint <= 0x1112B ?
                                    (codepoint <= 0x110B6 ?
                                        (codepoint <= 0x11081 ?
                                            codepoint >= 0x1107F :
                                            (codepoint >= 0x110B3 && codepoint <= 0x110B6)) :
                                        (codepoint <= 0x110BA ?
                                            codepoint >= 0x110B9 :
                                            (codepoint <= 0x11102 ?
                                                codepoint >= 0x11100 :
                                                (codepoint >= 0x11127 && codepoint <= 0x1112B)))) :
                                    (codepoint <= 0x11173 ?
                                        (codepoint <= 0x11134 ?
                                            codepoint >= 0x1112D :
                                            codepoint == 0x11173) :
                                        (codepoint <= 0x11181 ?
                                            codepoint >= 0x11180 :
                                            (codepoint <= 0x111BE ?
                                                codepoint >= 0x111B6 :
                                                (codepoint >= 0x111C9 && codepoint <= 0x111CC))))) :
                                (codepoint <= 0x1123E ?
                                    (codepoint <= 0x11231 ?
                                        (codepoint == 0x111CF ||
                                            (codepoint >= 0x1122F && codepoint <= 0x11231)) :
                                        (codepoint == 0x11234 ||
                                            (codepoint <= 0x11237 ?
                                                codepoint >= 0x11236 :
                                                codepoint == 0x1123E))) :
                                    (codepoint <= 0x11301 ?
                                        (codepoint == 0x112DF ||
                                            (codepoint <= 0x112EA ?
                                                codepoint >= 0x112E3 :
                                                (codepoint >= 0x11300 && codepoint <= 0x11301))) :
                                        (codepoint <= 0x1133C ?
                                            codepoint >= 0x1133B :
                                            (codepoint == 0x11340 ||
                                                (codepoint >= 0x11366 && codepoint <= 0x1136C)))))))) :
                    (codepoint <= 0x11C3F ?
                        (codepoint <= 0x1171F ?
                            (codepoint <= 0x115B5 ?
                                (codepoint <= 0x1145E ?
                                    (codepoint <= 0x1143F ?
                                        (codepoint <= 0x11374 ?
                                            codepoint >= 0x11370 :
                                            (codepoint >= 0x11438 && codepoint <= 0x1143F)) :
                                        (codepoint <= 0x11444 ?
                                            codepoint >= 0x11442 :
                                            (codepoint == 0x11446 ||
                                                codepoint == 0x1145E))) :
                                    (codepoint <= 0x114BA ?
                                        (codepoint <= 0x114B8 ?
                                            codepoint >= 0x114B3 :
                                            codepoint == 0x114BA) :
                                        (codepoint <= 0x114C0 ?
                                            codepoint >= 0x114BF :
                                            (codepoint <= 0x114C3 ?
                                                codepoint >= 0x114C2 :
                                                (codepoint >= 0x115B2 && codepoint <= 0x115B5))))) :
                                (codepoint <= 0x1163D ?
                                    (codepoint <= 0x115C0 ?
                                        (codepoint <= 0x115BD ?
                                            codepoint >= 0x115BC :
                                            (codepoint >= 0x115BF && codepoint <= 0x115C0)) :
                                        (codepoint <= 0x115DD ?
                                            codepoint >= 0x115DC :
                                            (codepoint <= 0x1163A ?
                                                codepoint >= 0x11633 :
                                                codepoint == 0x1163D))) :
                                    (codepoint <= 0x116AD ?
                                        (codepoint <= 0x11640 ?
                                            codepoint >= 0x1163F :
                                            (codepoint == 0x116AB ||
                                                codepoint == 0x116AD)) :
                                        (codepoint <= 0x116B5 ?
                                            codepoint >= 0x116B0 :
                                            (codepoint == 0x116B7 ||
                                                (codepoint >= 0x1171D && codepoint <= 0x1171F)))))) :
                            (codepoint <= 0x119E0 ?
                                (codepoint <= 0x1193C ?
                                    (codepoint <= 0x1172B ?
                                        (codepoint <= 0x11725 ?
                                            codepoint >= 0x11722 :
                                            (codepoint >= 0x11727 && codepoint <= 0x1172B)) :
                                        (codepoint <= 0x11837 ?
                                            codepoint >= 0x1182F :
                                            (codepoint <= 0x1183A ?
                                                codepoint >= 0x11839 :
                                                (codepoint >= 0x1193B && codepoint <= 0x1193C)))) :
                                    (codepoint <= 0x11943 ?
                                        (codepoint == 0x1193E ||
                                            codepoint == 0x11943) :
                                        (codepoint <= 0x119D7 ?
                                            codepoint >= 0x119D4 :
                                            (codepoint <= 0x119DB ?
                                                codepoint >= 0x119DA :
                                                codepoint == 0x119E0)))) :
                                (codepoint <= 0x11A56 ?
                                    (codepoint <= 0x11A38 ?
                                        (codepoint <= 0x11A0A ?
                                            codepoint >= 0x11A01 :
                                            (codepoint >= 0x11A33 && codepoint <= 0x11A38)) :
                                        (codepoint <= 0x11A3E ?
                                            codepoint >= 0x11A3B :
                                            (codepoint == 0x11A47 ||
                                                (codepoint >= 0x11A51 && codepoint <= 0x11A56)))) :
                                    (codepoint <= 0x11A99 ?
                                        (codepoint <= 0x11A5B ?
                                            codepoint >= 0x11A59 :
                                            (codepoint <= 0x11A96 ?
                                                codepoint >= 0x11A8A :
                                                (codepoint >= 0x11A98 && codepoint <= 0x11A99))) :
                                        (codepoint <= 0x11C36 ?
                                            codepoint >= 0x11C30 :
                                            (codepoint <= 0x11C3D ?
                                                codepoint >= 0x11C38 :
                                                codepoint == 0x11C3F)))))) :
                        (codepoint <= 0x1D182 ?
                            (codepoint <= 0x11D91 ?
                                (codepoint <= 0x11D36 ?
                                    (codepoint <= 0x11CB0 ?
                                        (codepoint <= 0x11CA7 ?
                                            codepoint >= 0x11C92 :
                                            (codepoint >= 0x11CAA && codepoint <= 0x11CB0)) :
                                        (codepoint <= 0x11CB3 ?
                                            codepoint >= 0x11CB2 :
                                            (codepoint <= 0x11CB6 ?
                                                codepoint >= 0x11CB5 :
                                                (codepoint >= 0x11D31 && codepoint <= 0x11D36)))) :
                                    (codepoint <= 0x11D3D ?
                                        (codepoint == 0x11D3A ||
                                            (codepoint >= 0x11D3C && codepoint <= 0x11D3D)) :
                                        (codepoint <= 0x11D45 ?
                                            codepoint >= 0x11D3F :
                                            (codepoint == 0x11D47 ||
                                                (codepoint >= 0x11D90 && codepoint <= 0x11D91))))) :
                                (codepoint <= 0x16B36 ?
                                    (codepoint <= 0x11D97 ?
                                        (codepoint == 0x11D95 ||
                                            codepoint == 0x11D97) :
                                        (codepoint <= 0x11EF4 ?
                                            codepoint >= 0x11EF3 :
                                            (codepoint <= 0x16AF4 ?
                                                codepoint >= 0x16AF0 :
                                                (codepoint >= 0x16B30 && codepoint <= 0x16B36)))) :
                                    (codepoint <= 0x16FE4 ?
                                        (codepoint == 0x16F4F ||
                                            (codepoint <= 0x16F92 ?
                                                codepoint >= 0x16F8F :
                                                codepoint == 0x16FE4)) :
                                        (codepoint <= 0x1BC9E ?
                                            codepoint >= 0x1BC9D :
                                            (codepoint <= 0x1D169 ?
                                                codepoint >= 0x1D167 :
                                                (codepoint >= 0x1D17B && codepoint <= 0x1D182)))))) :
                            (codepoint <= 0x1E006 ?
                                (codepoint <= 0x1DA6C ?
                                    (codepoint <= 0x1D1AD ?
                                        (codepoint <= 0x1D18B ?
                                            codepoint >= 0x1D185 :
                                            (codepoint >= 0x1D1AA && codepoint <= 0x1D1AD)) :
                                        (codepoint <= 0x1D244 ?
                                            codepoint >= 0x1D242 :
                                            (codepoint <= 0x1DA36 ?
                                                codepoint >= 0x1DA00 :
                                                (codepoint >= 0x1DA3B && codepoint <= 0x1DA6C)))) :
                                    (codepoint <= 0x1DA84 ?
                                        (codepoint == 0x1DA75 ||
                                            codepoint == 0x1DA84) :
                                        (codepoint <= 0x1DA9F ?
                                            codepoint >= 0x1DA9B :
                                            (codepoint <= 0x1DAAF ?
                                                codepoint >= 0x1DAA1 :
                                                (codepoint >= 0x1E000 && codepoint <= 0x1E006))))) :
                                (codepoint <= 0x1E136 ?
                                    (codepoint <= 0x1E021 ?
                                        (codepoint <= 0x1E018 ?
                                            codepoint >= 0x1E008 :
                                            (codepoint >= 0x1E01B && codepoint <= 0x1E021)) :
                                        (codepoint <= 0x1E024 ?
                                            codepoint >= 0x1E023 :
                                            (codepoint <= 0x1E02A ?
                                                codepoint >= 0x1E026 :
                                                (codepoint >= 0x1E130 && codepoint <= 0x1E136)))) :
                                    (codepoint <= 0x1E94A ?
                                        (codepoint <= 0x1E2EF ?
                                            codepoint >= 0x1E2EC :
                                            (codepoint <= 0x1E8D6 ?
                                                codepoint >= 0x1E8D0 :
                                                (codepoint >= 0x1E944 && codepoint <= 0x1E94A))) :
                                        (codepoint <= 0x1F3FF ?
                                            codepoint >= 0x1F3FB :
                                            (codepoint <= 0x1F9B3 ?
                                                codepoint >= 0x1F9B0 :
                                                (codepoint >= 0xE0100 && codepoint <= 0xE01EF))))))))))
        ) {
            // zero width
        } else if (
            // basic emojis only
            (codepoint <= 0x1F236 ?
                (codepoint <= 0x026FD ?
                    (codepoint <= 0x026A1 ?
                        (codepoint <= 0x025FE ?
                            (codepoint <= 0x023EC ?
                                (codepoint <= 0x0231B ?
                                    codepoint >= 0x0231A :
                                    (codepoint >= 0x023E9 && codepoint <= 0x023EC)) :
                                (codepoint == 0x023F0 ||
                                    (codepoint == 0x023F3 ||
                                        (codepoint >= 0x025FD && codepoint <= 0x025FE)))) :
                            (codepoint <= 0x02653 ?
                                (codepoint <= 0x02615 ?
                                    codepoint >= 0x02614 :
                                    (codepoint >= 0x02648 && codepoint <= 0x02653)) :
                                (codepoint == 0x0267F ||
                                    (codepoint == 0x02693 ||
                                        codepoint == 0x026A1)))) :
                        (codepoint <= 0x026D4 ?
                            (codepoint <= 0x026BE ?
                                (codepoint <= 0x026AB ?
                                    codepoint >= 0x026AA :
                                    (codepoint >= 0x026BD && codepoint <= 0x026BE)) :
                                (codepoint <= 0x026C5 ?
                                    codepoint >= 0x026C4 :
                                    (codepoint == 0x026CE ||
                                        codepoint == 0x026D4))) :
                            (codepoint <= 0x026F3 ?
                                (codepoint == 0x026EA ||
                                    (codepoint >= 0x026F2 && codepoint <= 0x026F3)) :
                                (codepoint == 0x026F5 ||
                                    (codepoint == 0x026FA ||
                                        codepoint == 0x026FD))))) :
                    (codepoint <= 0x027BF ?
                        (codepoint <= 0x0274E ?
                            (codepoint <= 0x0270B ?
                                (codepoint == 0x02705 ||
                                    (codepoint >= 0x0270A && codepoint <= 0x0270B)) :
                                (codepoint == 0x02728 ||
                                    (codepoint == 0x0274C ||
                                        codepoint == 0x0274E))) :
                            (codepoint <= 0x02757 ?
                                (codepoint <= 0x02755 ?
                                    codepoint >= 0x02753 :
                                    codepoint == 0x02757) :
                                (codepoint <= 0x02797 ?
                                    codepoint >= 0x02795 :
                                    (codepoint == 0x027B0 ||
                                        codepoint == 0x027BF)))) :
                        (codepoint <= 0x1F0CF ?
                            (codepoint <= 0x02B50 ?
                                (codepoint <= 0x02B1C ?
                                    codepoint >= 0x02B1B :
                                    codepoint == 0x02B50) :
                                (codepoint == 0x02B55 ||
                                    (codepoint == 0x1F004 ||
                                        codepoint == 0x1F0CF))) :
                            (codepoint <= 0x1F201 ?
                                (codepoint == 0x1F18E ||
                                    (codepoint <= 0x1F19A ?
                                        codepoint >= 0x1F191 :
                                        codepoint == 0x1F201)) :
                                (codepoint == 0x1F21A ||
                                    (codepoint == 0x1F22F ||
                                        (codepoint >= 0x1F232 && codepoint <= 0x1F236))))))) :
                (codepoint <= 0x1F64F ?
                    (codepoint <= 0x1F3F4 ?
                        (codepoint <= 0x1F37C ?
                            (codepoint <= 0x1F251 ?
                                (codepoint <= 0x1F23A ?
                                    codepoint >= 0x1F238 :
                                    (codepoint >= 0x1F250 && codepoint <= 0x1F251)) :
                                (codepoint <= 0x1F320 ?
                                    codepoint >= 0x1F300 :
                                    (codepoint <= 0x1F335 ?
                                        codepoint >= 0x1F32D :
                                        (codepoint >= 0x1F337 && codepoint <= 0x1F37C)))) :
                            (codepoint <= 0x1F3CA ?
                                (codepoint <= 0x1F393 ?
                                    codepoint >= 0x1F37E :
                                    (codepoint >= 0x1F3A0 && codepoint <= 0x1F3CA)) :
                                (codepoint <= 0x1F3D3 ?
                                    codepoint >= 0x1F3CF :
                                    (codepoint <= 0x1F3F0 ?
                                        codepoint >= 0x1F3E0 :
                                        codepoint == 0x1F3F4)))) :
                        (codepoint <= 0x1F54E ?
                            (codepoint <= 0x1F440 ?
                                (codepoint <= 0x1F43E ?
                                    codepoint >= 0x1F3F8 :
                                    codepoint == 0x1F440) :
                                (codepoint <= 0x1F4FC ?
                                    codepoint >= 0x1F442 :
                                    (codepoint <= 0x1F53D ?
                                        codepoint >= 0x1F4FF :
                                        (codepoint >= 0x1F54B && codepoint <= 0x1F54E)))) :
                            (codepoint <= 0x1F57A ?
                                (codepoint <= 0x1F567 ?
                                    codepoint >= 0x1F550 :
                                    codepoint == 0x1F57A) :
                                (codepoint <= 0x1F596 ?
                                    codepoint >= 0x1F595 :
                                    (codepoint == 0x1F5A4 ||
                                        (codepoint >= 0x1F5FB && codepoint <= 0x1F64F)))))) :
                    (codepoint <= 0x1F93A ?
                        (codepoint <= 0x1F6DF ?
                            (codepoint <= 0x1F6CC ?
                                (codepoint <= 0x1F6C5 ?
                                    codepoint >= 0x1F680 :
                                    codepoint == 0x1F6CC) :
                                (codepoint <= 0x1F6D2 ?
                                    codepoint >= 0x1F6D0 :
                                    (codepoint <= 0x1F6D7 ?
                                        codepoint >= 0x1F6D5 :
                                        (codepoint >= 0x1F6DD && codepoint <= 0x1F6DF)))) :
                            (codepoint <= 0x1F6FC ?
                                (codepoint <= 0x1F6EC ?
                                    codepoint >= 0x1F6EB :
                                    (codepoint >= 0x1F6F4 && codepoint <= 0x1F6FC)) :
                                (codepoint <= 0x1F7EB ?
                                    codepoint >= 0x1F7E0 :
                                    (codepoint == 0x1F7F0 ||
                                        (codepoint >= 0x1F90C && codepoint <= 0x1F93A))))) :
                        (codepoint <= 0x1FA86 ?
                            (codepoint <= 0x1F9FF ?
                                (codepoint <= 0x1F945 ?
                                    codepoint >= 0x1F93C :
                                    (codepoint >= 0x1F947 && codepoint <= 0x1F9FF)) :
                                (codepoint <= 0x1FA74 ?
                                    codepoint >= 0x1FA70 :
                                    (codepoint <= 0x1FA7C ?
                                        codepoint >= 0x1FA78 :
                                        (codepoint >= 0x1FA80 && codepoint <= 0x1FA86)))) :
                            (codepoint <= 0x1FAC5 ?
                                (codepoint <= 0x1FAAC ?
                                    codepoint >= 0x1FA90 :
                                    (codepoint <= 0x1FABA ?
                                        codepoint >= 0x1FAB0 :
                                        (codepoint >= 0x1FAC0 && codepoint <= 0x1FAC5))) :
                                (codepoint <= 0x1FAD9 ?
                                    codepoint >= 0x1FAD0 :
                                    (codepoint <= 0x1FAE7 ?
                                        codepoint >= 0x1FAE0 :
                                        (codepoint >= 0x1FAF0 && codepoint <= 0x1FAF6))))))))
        ) {
            // assume emojis are rendered 2 character wide?
            count += 2;
        } else {
            count += 1;
        }
    });
    // fprintf(stderr, "%3zu graphemes in \"", count);
    // fwrite(text, len, 1, stderr);
    // fprintf(stderr, "\"\n");
    return count;
}
