This is Gstreamer Tutorial project
 - 1. bus를 loop에서 poll 하여 구현하는 예시 
       pipe라인마다 bus를 얻어 loop를 돌려야 하므로, 1세션에 1thread가 필요해보인다.
 - 2. bus를 mainloop로 돌리는 구현 예시
       pipe라인에서 bus를 얻어 mainloop의 callback에 등록, gst_bus_add_signal_watch 함수를 사용하여 mainloop에서 signal watch 등록, 멀티세션에서 1개 메인 스레드만 사용하면 될것으로 보인다.