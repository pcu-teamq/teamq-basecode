## DIY 지문 인식 도어락

* 지문 인식 센서 jm-101B를 이용해 출입이 허가된 사람과 아닌 사람을 구분하고, 서보 모터로 경첩을 열고 닫음.
* 라이브러리의 기초 예제 파일인 delete, enroll은 그대로 사용했으며, fingerprint.ino만 아래의 소스 코드처럼 수정했습니다.

1. 지문 인식 센서에 사용자 지문 등록
2. 지문 등록 과정이 끝나면 아래의 아두이노 파일을 업로드
3. 작동중인 프로그램에 지문 검사를 하면 끝.
4. 출입 불허된 사람 LED, 부저 울리는 코드와, 서보모터 각도 조종하는 코드만 추가함.
  
  
**사용한 라이브러리** : 
* https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library
  
  
**사용한 센서** :
* [아두이노 우노](https://www.devicemart.co.kr/goods/view?no=1245596)
* [지문 인식 센서 + 커넥터](https://www.devicemart.co.kr/goods/view?no=12169464)
* [서보 모터](https://www.devicemart.co.kr/goods/view?no=12503476)
* [LED](https://www.devicemart.co.kr/goods/view?no=1320882)
* [패시브 부저](https://www.devicemart.co.kr/goods/view?no=1383969)
 
 
**보완점** : 
* 서보 모터로 구현한 출입 허용 및 차단 기능을 더 적합한 물체로 보완해야(경첩과 솔레노이드 등) 실 사용이 가능함
* 지문 인식 센서가 지문을 잘 인식하지 못함. 어쩔수 없는듯

 
**연결 완성 사진**
  
    
<img src="https://user-images.githubusercontent.com/36785390/94389150-066f3c80-018a-11eb-94e5-10f730b3b607.jpg" width="450" height="450">

**출처**
* https://gist.github.com/woorimlee/a05a2c0317ab0b3e67071ea661ba9c80
