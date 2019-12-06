int MEM[][LULU_PATCHSIZE] = {
  {0      , 0  , 0  , 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 0    , 0   , 0   },  // BLACK
  {0      , 0  , 0  , 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 0    , 0   , 0   },  // external
  {255    , 255, 255, 255, 255, 0      , 0        , 0       , 11      , 30        , 0      , 0      , 0      , 0      , 0         , 0          , 255  , 0   , 0   },  // str white
  {127    , 255, 0  , 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 255  , 0   , 0   },  // Red
  {127    , 0  , 255, 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 255  , 0   , 0   },  // Green
  {127    , 0  , 0  , 255, 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 255  , 0   , 0   },  // Blue
  {127    , 255, 255, 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 255  , 0   , 0   }   // Yellow
};
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , color_mod , mirror_mod , zoom , pw1 , pw2 }
uint8_t fakeframe[adr + LULU_PATCHSIZE];

void manu_frame(int mem) {
  for (int i = 0 ; i < LULU_PATCHSIZE; i++) fakeframe[adr + i - 1] = MEM[mem][i];
  onDmxFrame(LULU_UNI, adr + LULU_PATCHSIZE, 0, fakeframe);
}
