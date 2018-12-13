// ARTHOUSEView.cpp : CARTHOUSEView 클래스의 구현
//
#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ARTHOUSE.h"
#endif
#include "ARTHOUSEDoc.h"
#include "ARTHOUSEView.h"
#include "stdafx.h"
#include "Markup.h"			//XML 파싱 함수
#include "PictureEx.h"		//gif 출력 함수 
#include <locale.h>
#include <Urlmon.h>
#include <string>
#include "stdlib.h"
#pragma comment(lib,"urlmon.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//한결 서비스키
//#define SERVICEKEY_YJ _T("nrCjRlHdApJBoV34Bn63WHlKMH0n8JwKa35KIOEq93VvnjXhwTvZcjE1RxbWiLW2QDpN41hOIpKmml7M4M1nlg%3D%3D")
//범수 서비스키
#define SERVICEKEY_YJ _T("KQ%2BaEN2pHnvAO1lo%2BcZXD8U7bJsp6EMSqGgSBsuWJGcTppujpm3x0y%2Bvwbl7DP0ZYnpbXOx1TW7rIC5y7HjL8A%3D%3D")
//유진 서비스키
#define SERVICEKEY_YJ_2 _T("BWwY1m%2B1tAP%2Fe6UlY2ni1TjuIMq9H4nNuNS6UeMrBvAXCfFnPdVrMUCL%2FqbMYwz0qSc%2B1gTkPtnQpkY0vop1CQ%3D%3D")
#define mode0_nosel 0
#define mode0_sel 1
#define mode_bs_nosel 2
#define mode_bs_sel 3
#define mode_gj_nosel 4
#define mode_gj_sel 5
#define mode_dj_nosel 6
#define mode_dj_sel 7
#define mode_dg_nosel 8
#define mode_dg_sel 9
#define mode_su_nosel 10
#define mode_su_sel 11
#define mode_jj_nosel 12
#define mode_jj_sel 13
#define mode_ic_nosel 14
#define mode_ic_sel 15
#define mode_gw_nosel 16
#define mode_gw_sel 17
#define mode_cn_nosel 18
#define mode_cn_sel 19
#define mode_us_nosel 20
#define mode_us_sel 21
#define mode_jn_nosel 22
#define mode_jn_sel 23
#define mode_gn_nosel 24
#define mode_gn_sel 25
#define mode_jb_nosel 26
#define mode_jb_sel 27
#define mode_gg_nosel 28
#define mode_gg_sel 29
#define mode_cb_nosel 30
#define mode_cb_sel 31
#define mode_gb_nosel 32
#define mode_gb_sel 33
#define MAP_KO_RATIO_X 2 //클라이언트와 비율 n : 1
#define MAP_KO_RATIO_Y 1 //클라이언트와 비율 n : 1

CString str_dj[] = { _T("유성구"), _T("대덕구"), _T("동구"), _T("중구"), _T("서구") };
CString str_ic[] = { _T("강화군"), _T("서구"), _T("계양구"), _T("부평구"), _T("남동구"), _T("연수구"), _T("미추홀구"), _T("중구"), _T("동구"), _T("옹진군") };
CString str_su[] = { _T("강남구"), _T("송파구"), _T("관악구"), _T("영등포구"), _T("서대문구"), _T("용산구"), _T("동대문구"), _T("도봉구") };
CString str_gg[] = { _T("화성시"), _T("평택시"), _T("수원시"), _T("안양시"), _T("양평군"), _T("남양주시"), _T("포천시"), _T("연천군"), _T("파주시"), _T("동두천시"), _T("고양시") };
CString str_gw[] = { _T("철원군"), _T("춘천시"), _T("홍천군"), _T("원주시"), _T("평창군"), _T("강릉시"), _T("속초시") };
CString str_gb[] = { _T("문경시"), _T("구미시"), _T("경주시"), _T("포항시"), _T("영양군"), _T("안동시"), _T("청송군"), _T("김천시") };
CString str_dg[] = { _T("동구"), _T("북구"), _T("서구"), _T("중구"), _T("남구"), _T("달서구"), _T("수성구"), _T("달성군") };
CString str_us[] = { _T("울주군"), _T("북구"), _T("중구"), _T("남구"), _T("동구") };
CString str_bs[] = { _T("기장군"), _T("금정구"), _T("북구"), _T("강서구"), _T("사상구"), _T("사하구"), _T("서구"), _T("중구"), _T("동구"), _T("진구"), _T("영도구"), _T("남구"), _T("수영구"), _T("연제구"), _T("동래구"), _T("해운대구") };
CString str_gn[] = { _T("산청군"), _T("하동군"), _T("남해군"), _T("거제시"), _T("창원시"), _T("김해시"), _T("양산시"), _T("의령군"), _T("밀양시"), _T("거창군"), _T("진주시") };
CString str_jj[] = { _T("제주시"), _T("성산읍"), _T("중문"), _T("서귀포") };
CString str_jn[] = { _T("순천시"), _T("여수시"), _T("나주시"), _T("목포시"), _T("담양군"), _T("해남군"), _T("장흥군"), _T("보성군"), _T("완도군"), _T("진도군") };
CString str_gj[] = { _T("광산구"), _T("북구"), _T("동구"), _T("남구"), _T("서구") };
CString str_jb[] = { _T("무주군"), _T("남원시"), _T("순창군"), _T("고창군"), _T("전주시"), _T("익산시"), _T("완주군"), _T("군산시"), _T("정읍시"), _T("진안군") };
CString str_cn[] = { _T("천안시"), _T("아산시"), _T("공주시"), _T("청양군"), _T("보령시"), _T("서산시"), _T("태안군"), _T("논산시") };
CString str_cb[] = { _T("영동군"), _T("옥천군"), _T("보은군"), _T("청주시"), _T("괴산군"), _T("음성군"), _T("충주시"), _T("단양군") };

int xy_dj[] = { 67, 101, 68, 100, 68, 100, 68, 100, 67, 100 };
int xy_ic[] = { 51, 130, 55, 126, 56, 126, 55, 125, 56, 124, 55, 123, 54, 124, 54, 125, 54, 125, 54, 124 };
int xy_su[] = { 61, 126, 62, 126, 59, 125, 58, 126, 59, 127, 60, 126, 61, 127, 61, 129 };
int xy_gg[] = { 57, 119, 62, 114, 60, 121, 59, 123, 69, 125, 64, 128, 64, 134, 61, 138, 56, 131, 61, 134, 57, 128, };
int xy_gw[] = { 65, 139, 73, 134, 75, 130, 76, 122, 84, 123, 92, 131, 87, 141 };
int xy_gb[] = { 81, 106, 84, 96, 100, 91, 102, 94, 97, 108, 91, 106, 96, 103, 80, 96 };
int xy_dg[] = { 90, 91, 89, 91, 88, 90, 89, 90, 88, 90, 89, 90, 86, 88 };
int xy_us[] = { 101, 84, 103, 85, 102, 84, 102, 84, 104, 83 };
int xy_bs[] = { 100, 77, 98, 77, 96, 76, 96, 76, 96, 75, 96, 74, 96, 76, 96, 74, 98, 75, 97, 75, 98, 74, 98, 75, 99, 75, 98, 76, 98, 76, 99, 75 };
int xy_gn[] = { 76, 80, 74, 73, 77, 68, 90, 69, 90, 77, 95, 77, 97, 79, 83, 78, 92, 83, 77, 86, 81, 75 };
int xy_jj[] = { 53, 38, 60, 37, 51, 32, 52, 33 };
int xy_jn[] = { 70, 70, 73, 66, 56, 71, 50, 67, 61, 78, 54, 61, 59, 64, 62, 66, 57, 56, 48, 59 };
int xy_gj[] = { 57, 74, 59, 75, 60, 74, 59, 73, 59, 74 };
int xy_jb[] = { 72, 93, 68, 80, 63, 79, 56, 80, 63, 89, 60, 91, 63, 89, 56, 92, 58, 83, 68, 88 };
int xy_cn[] = { 63, 110, 60, 110, 63, 102, 57, 103, 54, 100, 51, 110, 48, 109, 62, 97 };
int xy_cb[] = { 74, 97, 71, 99, 73, 103, 69, 106, 74, 111, 72, 113, 76, 114, 84, 115 };

int pt_dj[] =
{
	363, 346
	, 606, 239
	, 670, 477
	, 528, 582
	, 391, 584
	, 0, 3
};
int pt_ic[] =
{
	540, 189
	, 814, 405
	, 909, 410
	, 917, 498
	, 918, 582
	, 833, 606
	, 843, 551
	, 759, 535
	, 751, 473
	, 569, 799
	, 0, 0
};
int pt_su[] =
{
	701, 659
	, 816, 610
	, 468, 719
	, 375, 564
	, 447, 393
	, 524, 514
	, 683, 400
	, 647, 133
	, 0, 0
};
int pt_gg[] =
{
	390, 688
	, 492, 799
	, 498, 628
	, 432, 567
	, 824, 490
	, 614, 395
	, 622, 202
	, 505, 134
	, 361, 280
	, 543, 238
	, 405, 402
	, 0, 0
};
int pt_gw[] =
{
	175, 203
	, 330, 392
	, 464, 459
	, 392, 726
	, 609, 574
	, 777, 484
	, 656, 247
	, 0, 1
};
int pt_gb[] =
{
	226, 257
	, 307, 501
	, 669, 681
	, 679, 531
	, 633, 261
	, 490, 311
	, 607, 433
	, 200, 576
	, 0, 7
};
int pt_dg[] =
{
	806, 187
	, 642, 201
	, 604, 316
	, 677, 300
	, 669, 393
	, 561, 401
	, 773, 407
	, 504, 567
	, 0, 7
};
int pt_us[] =
{
	378, 332
	, 765, 262
	, 643, 352
	, 675, 447
	, 849, 418
	, 0, 8
};
int pt_bs[] =
{
	766, 218
	, 590, 321
	, 477, 406
	, 290, 566
	, 417, 553
	, 392, 722
	, 464, 678
	, 505, 692
	, 515, 638
	, 502, 550
	, 545, 761
	, 594, 644
	, 628, 561
	, 583, 512
	, 572, 439
	, 686, 491
	, 0, 8
};
int pt_gn[] =
{
	232, 425
	, 191, 569
	, 251, 754
	, 559, 743
	, 540, 530
	, 656, 482
	, 741, 411
	, 406, 418
	, 617, 359
	, 246, 201
	, 338, 525
	, 0, 8
};
int pt_jj[] =
{
	466, 226
	, 842, 277
	, 449, 522
	, 591, 499
	, 0, 9
};
int pt_jn[] =
{
	763, 385
	, 886, 495
	, 457, 390
	, 314, 476
	, 590, 227
	, 382, 633
	, 555, 508
	, 666, 476
	, 454, 728
	, 239, 675
	, 0, 5
};
int pt_gj[] =
{
	360, 365
	, 700, 275
	, 804, 580
	, 618, 664
	, 575, 502
	, 0, 5
};
int pt_jb[] =
{
	580, 265
	, 739, 713
	, 599, 714
	, 352, 706
	, 596, 361
	, 532, 205
	, 626, 260
	, 401, 257
	, 461, 554
	, 716, 377
	, 0, 6
};
int pt_cn[] =
{
	715, 264
	, 593, 265
	, 650, 462
	, 521, 507
	, 358, 583
	, 288, 270
	, 155, 272
	, 689, 707
	, 0, 3
};
int pt_cb[] =
{
	440, 778
	, 360, 662
	, 399, 528
	, 249, 429
	, 430, 342
	, 312, 215
	, 485, 171
	, 792, 185
	, 0, 4
};
bool state_thread = FALSE;
//프로그램 실행 시 동작하는 스레드. 60초마다 파싱함수 호출.
int Representative_City[]
{
	60, 127,   // 서울
	60, 120,   // 경기도
	55, 124,   // 인천
	73, 134,   // 강원도
	67, 100,   // 대전
	68, 100,   // 충청남도
	69, 107,   // 충청북도
	58, 74,      // 광주
	51, 67,      // 전라남도
	63, 89,      // 전라북도
	89, 90,      // 대구
	102, 84,   // 울산
	91, 77,      // 경상남도
	89, 91,      // 경상북도
	98, 76,      // 부산
	52, 38      // 제주
};
int Representative_City_Cloud[16];   // 16개 도,광역시 강수형태 or 구름상태 정보.  초기 화면에 출력
									 // 맑음(1), 구름조금(2), 구름많음(3), 흐림(4), 비(5), 비/눈(6), 눈(7)
int Representative_City_temperature[16]; //16개 도,광역시 온도 정보 저장. 초기 화면에 출력.
int Thread_num = 0;					//스레드 변수
int mode = mode0_nosel;				//화면 출력 모드 변수
CString Weahter_info;
int width, height, weahter_length;
CStringArray array;
// * 강수확률, 구름상태 : 동네예보 / 강수형태, 습도, 현재온도 : 단기실황 *
CString Weather_Value[6];      // 강수확률, 구름상태, 현재온도, 강수량, 습도, 강수형태 
							   // 강수확률 : 없음(0), 비(1), 비/눈(2), 눈(3)
							   // 구름상태 : 맑음(1), 구름조금(2), 구름많음(3), 흐림(4)

int Weather_OneWeek_TMN[6];   // 1주일 최저기온
int Weather_OneWeek_TMX[6];   // 1주일 최고기온
CString Weather_OneWeek_Am_SKY[6];   //1주일 오전 구름 상태
CString Weather_OneWeek_Pm_SKY[6];   //1주일 오후 구름 상태

									 // 서울·인천·경기도(0), 강원도영서(1), 강원도영동(2), 대전·세종·충청남도(3), 충청북도(4), 광주·전라남도(5)
									 // 전라북도(6), 대구·경상북도(7), 부산·울산·경상남도(8), 제주도(9)
CString Cloud_YeBo_Code[10] = { _T("11B00000"), _T("11D10000"), _T("11D20000"), _T("11C20000"), _T("11C10000"),
_T("11F20000"), _T("11F10000"), _T("11H10000"), _T("11H20000"), _T("11G00000") };

CString temperature_YeBo_Code[10] = { _T("11B10101"), _T("11D10301"), _T("11D20501"), _T("11C20401"), _T("11C10301"),
_T("11F20501"), _T("11F10201"), _T("11H10701"), _T("11H20201"), _T("11G00201") };

int fine_dust[10];		// 미세먼지
int Ultrafine_dust[10];	// 초미세먼지
CEvent g_event(FALSE, TRUE); // 이벤트 변수 선언

							 // CChildView 메시지 처리기
CRgn rgn_bs, rgn_cb, rgn_cn, rgn_dg, rgn_dj, rgn_gb, rgn_gg, rgn_gj, rgn_gn, rgn_gw, rgn_ic, rgn_jb, rgn_jj, rgn_jn, rgn_su, rgn_us, rgn_cb1, rgn_cb2, rgn_back;
CRect rect_client;
CPoint pt_zero(0, 0);
CString str;
CDC dcmem1;
CBitmap* pOldBmp = NULL;

// CString to int 변환
int CStringToint(CString str)
{
	int int_num = _ttoi(str);
	return int_num;
}

//  동네예보함수 지역 x,y 좌표
void DongNeYeBo_City_Find(int x, int y)         
{
	CMarkup xml;								// 동네예보 xml파일
	CTime cTime = CTime::GetCurrentTime();      // 현재시간
	CString strDate = _T(""), strTime = _T(""); // 문자열 초기화
	CString Address, Address_more;				// 주소 
	CString DongNeYeBo = _T("http://newsky2.kma.go.kr/service/SecndSrtpdFrcstInfoService2/ForecastSpaceData");     
												// 동네예보 주소 앞부분
	CString nx, ny;								// 지역 x,y 좌표
	CString str_cmp_Date, str_cmp_Time;			// 문자열 비교 
	CString fcstDate, fcstTime;					// 날짜, 시간변수
	CString str_note;							// 문자열 저장소

	int info_POP = 0, info_SKY = 0, info_TMN = 0, info_TMX = 0, info_Am = 0, info_Pm = 0, info_time = 0;// 정보 변수

																										// int to CString 변환
	nx.Format(_T("%d"), x);
	ny.Format(_T("%d"), y);

	// String to int 
	CString strTime1 = _T("");
	strTime1.Format(_T("%02d"), cTime.GetHour());
	int a = CStringToint(strTime1);

	if (a < 2) {
		// Data, Time 값 strDate, strTime 변수에 저장
		strDate.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay() - 1);
		fcstDate.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());
		info_time = 0;
		strTime = _T("230000");
	}
	else {
		// Data, Time 값 strDate, strTime 변수에 저장
		strDate.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());
		fcstDate.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay() + 1);
		strTime.Format(_T("%02d0000"), (cTime.GetHour() + 1) / 3 * 3 - 1);
		info_time = 1;
	}

	// 뒤에 추가적으로 들어가는 주소 
	Address_more = _T("&numOfRows=500&pageSize=10&pageNo=1&startPage=1&_type=xml");

	// 총 들어가는 주소
	Address = DongNeYeBo + _T("?serviceKey=") + SERVICEKEY_YJ + _T("&base_date=") + strDate + _T("&base_time=")
				+ strTime + _T("&nx=") + nx + _T("&ny=") + ny + Address_more;
	// 주소에 들어가서 주소에 있는 내용 Weather.XML 생성
	HRESULT res = URLDownloadToFile(NULL, Address, _T("Weather.XML"), 0, NULL);      

	CString strFileName = _T("Weather.XML");

	if (xml.Load(strFileName) != true)      // Weather.XML 파일 로드
	{
		AfxMessageBox(_T("파일이 없습니다."));   // 실패하면 뜨는 메시지 박스
		return;
	}

	// rseponse 카테고리 안
	xml.FindElem(_T("response"));      // response 정보를 찾는다.
	xml.IntoElem();                  // response 안의 내용 확인.

									 // body 카테고리 안
	xml.FindElem(_T("body"));         // body 정보를 찾는다.
	xml.IntoElem();                  // response->body 안의 내용 확인

									 // items 카테고리 안
	xml.FindElem(_T("items"));         // item 정보를 찾는다.
	xml.IntoElem();                  // response -> body -> items 안의 내용 확인

	for (int i = 0; i < 500; i++)
	{
		xml.FindElem(_T("item"));
		xml.IntoElem();
		xml.FindElem(_T("category"));

		if (_T("POP") == xml.GetData() && info_POP == 0)
		{
			xml.FindElem(_T("fcstValue"));      // 강수확률 내용을 찾는다.
			Weather_Value[0] = xml.GetData();
			info_POP = 1;                  // 첫번째 강수확률 정보확인 
		}

		else if (_T("SKY") == xml.GetData())
		{
			xml.FindElem(_T("fcstDate"));
			str_cmp_Date = xml.GetData();         // fcstDate 값 변수에 저장

			if (fcstDate == str_cmp_Date)
			{
				xml.FindElem(_T("fcstTime"));
				str_cmp_Time = xml.GetData();
				if ((_T("0600") == str_cmp_Time) || (_T("1800") == str_cmp_Time))
				{
					xml.FindElem(_T("fcstValue"));      // 구름상태 내용을 찾는다.
					str_note = xml.GetData();

					//맑음(1), 구름조금(2), 구름많음(3), 흐림(4)
					if (_T("1") == str_note)
						str_note = _T("맑음");
					else if (_T("2") == str_note)
						str_note = _T("구름조금");
					else if (_T("3") == str_note)
						str_note = _T("구름많음");
					else if (_T("4") == str_note)
						str_note = _T("흐림");

					if (_T("0600") == str_cmp_Time)
					{
						Weather_OneWeek_Am_SKY[info_Am] = str_note;
						fcstTime = _T("1800");
					}

					else
					{
						Weather_OneWeek_Pm_SKY[info_Pm] = str_note;
						info_Am++;
						info_Pm++;
						fcstTime = _T("0600");
					}
				}
			}

			if (info_Pm == 1)
			{
				if (info_time)
					fcstDate.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay() + 2);
				else
					fcstDate.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay() + 1);
			}

			if (info_SKY == 0)
			{
				xml.FindElem(_T("fcstValue"));      // 구름상태 내용을 찾는다.
				Weather_Value[1] = xml.GetData();

				if (Representative_City_Cloud[Thread_num] == 4)
				{
					Representative_City_Cloud[Thread_num] = CStringToint(xml.GetData());
				}
				info_SKY = 1;                  // 첫번째 구름상태 정보확인
			}
		}

		else if (_T("TMN") == xml.GetData())
		{
			xml.FindElem(_T("fcstValue"));            // 최저기온 내용을 찾는다.
			Weather_OneWeek_TMN[info_TMN] = CStringToint(xml.GetData());
			info_TMN++;
		}

		else if (_T("TMX") == xml.GetData())
		{
			xml.FindElem(_T("fcstValue"));            // 최고기온 내용을 찾는다.
			Weather_OneWeek_TMX[info_TMX] = CStringToint(xml.GetData());
			info_TMX++;
		}
		xml.OutOfElem();
	}

	xml.OutOfElem();               // items 카테고리 탈출.
	xml.OutOfElem();               // body 카테고리 탈출.
	xml.OutOfElem();               // response 카테고리 탈출.
}
//  단기실황함수 지역 x,y 좌표
void DanGi_City_Find(int x, int y)            
{
	CMarkup xml;                        // 단기실황 xml파일
	CTime cTime = CTime::GetCurrentTime();      // 현재시간
	CString strDate = _T(""), strTime = _T(""); // 문자열 초기화
	CString Address, Address_more;            // 주소 
	CString DanGi = _T("http://newsky2.kma.go.kr/service/SecndSrtpdFrcstInfoService2/ForecastGrib");      // 단기실황 주소 앞부분
	CString nx, ny;                        // 지역 x,y 좌표

										   // int to CString 변환
	nx.Format(_T("%d"), x);
	ny.Format(_T("%d"), y);

	// Data, Time 값 strDate, strTime 변수에 저장
	strDate.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());
	strTime.Format(_T("%02d0000"), cTime.GetHour() - 1);

	// 뒤에 추가적으로 들어가는 주소 
	Address_more = _T("&numOfRows=10&pageSize=10&pageNo=1&startPage=1&_type=xml");

	// 총 들어가는 주소
	Address = DanGi + _T("?serviceKey=") + SERVICEKEY_YJ + _T("&base_date=") + strDate + _T("&base_time=") + strTime + _T("&nx=") + nx + _T("&ny=") + ny + Address_more;
	HRESULT res = URLDownloadToFile(NULL, Address, _T("Weather2.XML"), 0, NULL);      // 주소에 들어가서 주소에 있는 내용 Weather2.XML 생성

	CString strFileName = _T("Weather2.XML");

	if (xml.Load(strFileName) != true)      // Weather.XML 파일 로드
	{
		AfxMessageBox(_T("파일이 없습니다."));   // 실패하면 뜨는 메시지 박스
		return;
	}

	// rseponse 카테고리 안
	xml.FindElem(_T("response"));      // response 정보를 찾는다.
	xml.IntoElem();                  // response 안의 내용 확인.

									 // body 카테고리 안
	xml.FindElem(_T("body"));         // body 정보를 찾는다.
	xml.IntoElem();                  // response->body 안의 내용 확인

									 // items 카테고리 안
	xml.FindElem(_T("items"));         // item 정보를 찾는다.
	xml.IntoElem();                  // response -> body -> items 안의 내용 확인

	for (int i = 0; i < 10; i++)
	{
		xml.FindElem(_T("item"));
		xml.IntoElem();
		xml.FindElem(_T("category"));

		if (_T("T1H") == xml.GetData())
		{
			xml.FindElem(_T("obsrValue"));      // 기온 내용을 찾는다.
			Weather_Value[2] = xml.GetData();
			Representative_City_temperature[Thread_num] = CStringToint(xml.GetData());
		}

		else if (_T("RN1") == xml.GetData())
		{
			xml.FindElem(_T("obsrValue"));      // 강수량 내용을 찾는다.
			Weather_Value[3] = xml.GetData();
		}

		else if (_T("REH") == xml.GetData())
		{
			xml.FindElem(_T("obsrValue"));      // 습도 내용을 찾는다.
			Weather_Value[4] = xml.GetData();
		}

		else if (_T("PTY") == xml.GetData())
		{
			xml.FindElem(_T("obsrValue"));      // 강수형태 내용을 찾는다.
			Weather_Value[5] = xml.GetData();
			Representative_City_Cloud[Thread_num] = CStringToint(xml.GetData()) + (int)4;

		}
		xml.OutOfElem();
	}
	xml.OutOfElem();               // items 카테고리 탈출.
	xml.OutOfElem();               // body 카테고리 탈출.
	xml.OutOfElem();               // response 카테고리 탈출.
}
// 중기예보함수 지역 x,y 좌표
void Middle_Cloud_Find(CString Code)           
{
	CMarkup xml;                        // 중기예보 xml파일
	CTime cTime = CTime::GetCurrentTime();      // 현재시간
	CString strDate = _T(""), strTime = _T(""); // 문자열 초기화
	CString Address, Address_more;            // 주소 
	CString Middle = _T("http://newsky2.kma.go.kr/service/MiddleFrcstInfoService/getMiddleLandWeather");      // 중기예보 주소 앞부분
	CString str_cmp;                     // 문자열 비교
	CString strDate1 = _T(""), strTime1 = _T("");         // 비교할 날짜, 시간

														  // Data, Time 값 strDate, strTime 변수에 저장
	strDate1.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());
	strTime1.Format(_T("%02d%02d"), cTime.GetHour(), cTime.GetMinute());
	int a = _ttoi(strTime1);

	if (a >= 600) {
		// Data, Time 값 strDate, strTime 변수에 저장
		strDate.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());
		strTime.Format(_T("0600"));
	}
	else {
		strDate.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay() - 1);
		strTime.Format(_T("0600"));
	}

	// 뒤에 추가적으로 들어가는 주소 
	Address_more = _T("&numOfRows=10&pageSize=10&pageNo=1&startPage=1");

	// 총 들어가는 주소
	Address = Middle + _T("?serviceKey=") + SERVICEKEY_YJ + _T("&regId=") + Code + _T("&tmFc=") + strDate + strTime + Address_more;
	HRESULT res = URLDownloadToFile(NULL, Address, _T("Weather3.XML"), 0, NULL);      // 주소에 들어가서 주소에 있는 내용 Weather2.XML 생성

	CString strFileName = _T("Weather3.XML");

	if (xml.Load(strFileName) != true)      // Weather.XML 파일 로드
	{
		AfxMessageBox(_T("파일이 없습니다."));   // 실패하면 뜨는 메시지 박스
		return;
	}

	// rseponse 카테고리 안
	xml.FindElem(_T("response"));      // response 정보를 찾는다.
	xml.IntoElem();                  // response 안의 내용 확인.

									 // body 카테고리 안
	xml.FindElem(_T("body"));         // body 정보를 찾는다.
	xml.IntoElem();                  // response->body 안의 내용 확인

									 // items 카테고리 안
	xml.FindElem(_T("items"));       // items 정보를 찾는다.
	xml.IntoElem();                  // response -> body -> items 안의 내용 확인

									 // item 카테고리 안
	xml.FindElem(_T("item"));      // item 정보를 찾는다.
	xml.IntoElem();               // response -> body -> items -> item안의 내용 확인

								  //
	xml.FindElem(_T("wf3Am"));
	Weather_OneWeek_Am_SKY[2] = xml.GetData();
	xml.FindElem(_T("wf3Pm"));
	Weather_OneWeek_Pm_SKY[2] = xml.GetData();
	xml.FindElem(_T("wf4Am"));
	Weather_OneWeek_Am_SKY[3] = xml.GetData();
	xml.FindElem(_T("wf4Pm"));
	Weather_OneWeek_Pm_SKY[3] = xml.GetData();
	xml.FindElem(_T("wf5Am"));
	Weather_OneWeek_Am_SKY[4] = xml.GetData();
	xml.FindElem(_T("wf5Pm"));
	Weather_OneWeek_Pm_SKY[4] = xml.GetData();
	xml.FindElem(_T("wf6Am"));
	Weather_OneWeek_Am_SKY[5] = xml.GetData();
	xml.FindElem(_T("wf6Pm"));
	Weather_OneWeek_Pm_SKY[5] = xml.GetData();

	xml.OutOfElem();               // item 카테고리 탈출.
	xml.OutOfElem();               // items 카테고리 탈출.
	xml.OutOfElem();               // body 카테고리 탈출.
	xml.OutOfElem();               // response 카테고리 탈출.
}
// 중기예보함수 지역 x,y 좌표
void Middle_temperature_Find(CString Code)            
{
	CMarkup xml;                        // 중기예보 xml파일
	CTime cTime = CTime::GetCurrentTime();      // 현재시간
	CString strDate = _T(""), strTime = _T(""); // 문자열 초기화
	CString Address, Address_more;            // 주소 
	CString Middle = _T("http://newsky2.kma.go.kr/service/MiddleFrcstInfoService/getMiddleTemperature");      // 중기예보 주소 앞부분
	CString str_cmp;                     // 문자열 비교
	CString strDate1 = _T(""), strTime1 = _T("");         // 비교할 날짜, 시간

														  // Data, Time 값 strDate, strTime 변수에 저장
	strDate1.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());
	strTime1.Format(_T("%02d%02d"), cTime.GetHour(), cTime.GetMinute());
	int a = _ttoi(strTime1);
	if (a >= 600) {
		// Data, Time 값 strDate, strTime 변수에 저장
		strDate.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());
		strTime.Format(_T("0600"));
	}
	else {
		strDate.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay() - 1);
		strTime.Format(_T("0600"));
	}


	// 뒤에 추가적으로 들어가는 주소 
	Address_more = _T("&pageNo=1&startPage=1&numOfRows=10&pageSize=10");

	// 총 들어가는 주소
	Address = Middle + _T("?serviceKey=") + SERVICEKEY_YJ + _T("&regId=") + Code + _T("&tmFc=") + strDate + strTime + Address_more;
	HRESULT res = URLDownloadToFile(NULL, Address, _T("Weather4.XML"), 0, NULL);      // 주소에 들어가서 주소에 있는 내용 Weather2.XML 생성

	CString strFileName = _T("Weather4.XML");

	if (xml.Load(strFileName) != true)      // Weather.XML 파일 로드
	{
		AfxMessageBox(_T("파일이 없습니다."));   // 실패하면 뜨는 메시지 박스
		return;
	}

	// rseponse 카테고리 안
	xml.FindElem(_T("response"));      // response 정보를 찾는다.
	xml.IntoElem();                  // response 안의 내용 확인.

									 // body 카테고리 안
	xml.FindElem(_T("body"));         // body 정보를 찾는다.
	xml.IntoElem();                  // response->body 안의 내용 확인

									 // items 카테고리 안
	xml.FindElem(_T("items"));       // items 정보를 찾는다.
	xml.IntoElem();                  // response -> body -> items 안의 내용 확인

									 // item 카테고리 안
	xml.FindElem(_T("item"));      // item 정보를 찾는다.
	xml.IntoElem();               // response -> body -> items -> item안의 내용 확인

	xml.FindElem(_T("taMax3"));
	Weather_OneWeek_TMX[2] = CStringToint(xml.GetData());
	xml.FindElem(_T("taMax4"));
	Weather_OneWeek_TMX[3] = CStringToint(xml.GetData());
	xml.FindElem(_T("taMax5"));
	Weather_OneWeek_TMX[4] = CStringToint(xml.GetData());
	xml.FindElem(_T("taMax6"));
	Weather_OneWeek_TMX[5] = CStringToint(xml.GetData());
	xml.FindElem(_T("taMin3"));
	Weather_OneWeek_TMN[2] = CStringToint(xml.GetData());
	xml.FindElem(_T("taMin4"));
	Weather_OneWeek_TMN[3] = CStringToint(xml.GetData());
	xml.FindElem(_T("taMin5"));
	Weather_OneWeek_TMN[4] = CStringToint(xml.GetData());
	xml.FindElem(_T("taMin6"));
	Weather_OneWeek_TMN[5] = CStringToint(xml.GetData());

	xml.OutOfElem();               // item 카테고리 탈출.
	xml.OutOfElem();               // items 카테고리 탈출.
	xml.OutOfElem();               // body 카테고리 탈출.
	xml.OutOfElem();               // response 카테고리 탈출.
}
// 미세먼지 함수
void Fine_dust_Find()            
{
	CMarkup xml;                        // 미세먼지 xml파일
	CString Address, Address_more;            // 주소 
	CString Fine_dust;

	// 주소
	Fine_dust = _T("http://openapi.airkorea.or.kr/openapi/services/rest/ArpltnInforInqireSvc/getCtprvnMesureLIst");
	Address_more = _T("&numOfRows=10&pageSize=10&pageNo=1&startPage=1&itemCode=PM10&dataGubun=HOUR&searchCondition=MONTH");

	// 총 들어가는 주소
	Address = Fine_dust + _T("?serviceKey=") + SERVICEKEY_YJ + Address_more;
	HRESULT res = URLDownloadToFile(NULL, Address, _T("Fine_dust.XML"), 0, NULL);      // 주소에 들어가서 주소에 있는 내용 Fine_dust.XML 생성

	CString strFileName = _T("Fine_dust.XML");

	if (xml.Load(strFileName) != true)      // Weather.XML 파일 로드
	{
		AfxMessageBox(_T("파일이 없습니다."));   // 실패하면 뜨는 메시지 박스
		return;
	}

	// rseponse 카테고리 안
	xml.FindElem(_T("response"));      // response 정보를 찾는다.
	xml.IntoElem();                  // response 안의 내용 확인.

									 // body 카테고리 안
	xml.FindElem(_T("body"));         // body 정보를 찾는다.
	xml.IntoElem();                  // response->body 안의 내용 확인

									 // items 카테고리 안
	xml.FindElem(_T("items"));       // items 정보를 찾는다.
	xml.IntoElem();                  // response -> body -> items 안의 내용 확인

									 // item 카테고리 안
	xml.FindElem(_T("item"));      // item 정보를 찾는다.
	xml.IntoElem();               // response -> body -> items -> item안의 내용 확인

								  // 서울·인천·경기도(0), 강원도영서(1), 강원도영동(2), 대전·세종·충청남도(3), 충청북도(4), 광주·전라남도(5)
								  // 전라북도(6), 대구·경상북도(7), 부산·울산·경상남도(8), 제주도(9)

	xml.FindElem(_T("seoul"));      // seoul 지역 미세먼지
	fine_dust[0] = CStringToint(xml.GetData());

	xml.FindElem(_T("busan"));      // busan 지역 미세먼지
	fine_dust[8] = CStringToint(xml.GetData());

	xml.FindElem(_T("daegu"));      // daegu 지역 미세먼지
	fine_dust[7] = CStringToint(xml.GetData());

	xml.FindElem(_T("gwangju"));   // 광주 지역 미세먼지
	fine_dust[5] = CStringToint(xml.GetData());

	xml.FindElem(_T("daejeon"));   // 대전 지역 미세먼지
	fine_dust[3] = CStringToint(xml.GetData());

	xml.FindElem(_T("gangwon"));   // 강원도 지역 미세먼지
	fine_dust[1] = CStringToint(xml.GetData());
	fine_dust[2] = CStringToint(xml.GetData());

	xml.FindElem(_T("chungbuk"));   // 충청북도 지역 미세먼지
	fine_dust[4] = CStringToint(xml.GetData());

	xml.FindElem(_T("gyeongbuk"));   // 전라북도 지역 미세먼지
	fine_dust[6] = CStringToint(xml.GetData());

	xml.FindElem(_T("jeju"));      // jeju 지역 미세먼지
	fine_dust[9] = CStringToint(xml.GetData());

	xml.OutOfElem();               // item 카테고리 탈출.
	xml.OutOfElem();               // items 카테고리 탈출.
	xml.OutOfElem();               // body 카테고리 탈출.
	xml.OutOfElem();               // response 카테고리 탈출.
}
// 초미세먼지 함수
void Ultrafine_dust_Find()            
{
	CMarkup xml;                        // 미세먼지 xml파일
	CString Address, Address_more;            // 주소 
	CString dust;

	// 주소
	dust = _T("http://openapi.airkorea.or.kr/openapi/services/rest/ArpltnInforInqireSvc/getCtprvnMesureLIst");
	Address_more = _T("&numOfRows=10&pageSize=10&pageNo=1&startPage=1&itemCode=PM25&dataGubun=HOUR&searchCondition=MONTH");

	// 총 들어가는 주소
	Address = dust + _T("?serviceKey=") + SERVICEKEY_YJ + Address_more;
	HRESULT res = URLDownloadToFile(NULL, Address, _T("Ultrafine_dust.XML"), 0, NULL);      // 주소에 들어가서 주소에 있는 내용 Fine_dust.XML 생성

	CString strFileName = _T("Ultrafine_dust.XML");

	if (xml.Load(strFileName) != true)      // Weather.XML 파일 로드
	{
		AfxMessageBox(_T("파일이 없습니다."));   // 실패하면 뜨는 메시지 박스
		return;
	}

	// rseponse 카테고리 안
	xml.FindElem(_T("response"));      // response 정보를 찾는다.
	xml.IntoElem();                  // response 안의 내용 확인.

									 // body 카테고리 안
	xml.FindElem(_T("body"));         // body 정보를 찾는다.
	xml.IntoElem();                  // response->body 안의 내용 확인

									 // items 카테고리 안
	xml.FindElem(_T("items"));       // items 정보를 찾는다.
	xml.IntoElem();                  // response -> body -> items 안의 내용 확인

									 // item 카테고리 안
	xml.FindElem(_T("item"));      // item 정보를 찾는다.
	xml.IntoElem();               // response -> body -> items -> item안의 내용 확인

								  // 서울·인천·경기도(0), 강원도영서(1), 강원도영동(2), 대전·세종·충청남도(3), 충청북도(4), 광주·전라남도(5)
								  // 전라북도(6), 대구·경상북도(7), 부산·울산·경상남도(8), 제주도(9)

	xml.FindElem(_T("seoul"));      // seoul 지역 초미세먼지
	Ultrafine_dust[0] = CStringToint(xml.GetData());

	xml.FindElem(_T("busan"));      // busan 지역 초미세먼지
	Ultrafine_dust[8] = CStringToint(xml.GetData());

	xml.FindElem(_T("daegu"));      // daegu 지역 초미세먼지
	Ultrafine_dust[7] = CStringToint(xml.GetData());

	xml.FindElem(_T("gwangju"));   // 광주 지역 초미세먼지
	Ultrafine_dust[5] = CStringToint(xml.GetData());

	xml.FindElem(_T("daejeon"));   // 대전 지역 초미세먼지
	Ultrafine_dust[3] = CStringToint(xml.GetData());

	xml.FindElem(_T("gangwon"));   // 강원도 지역 초미세먼지
	Ultrafine_dust[1] = CStringToint(xml.GetData());
	Ultrafine_dust[2] = CStringToint(xml.GetData());

	xml.FindElem(_T("chungbuk"));   // 충청북도 지역 초미세먼지
	Ultrafine_dust[4] = CStringToint(xml.GetData());

	xml.FindElem(_T("gyeongbuk"));   // 전라북도 지역 초미세먼지
	Ultrafine_dust[6] = CStringToint(xml.GetData());

	xml.FindElem(_T("jeju"));      // jeju 지역 초미세먼지
	Ultrafine_dust[9] = CStringToint(xml.GetData());

	xml.OutOfElem();               // item 카테고리 탈출.
	xml.OutOfElem();               // items 카테고리 탈출.
	xml.OutOfElem();               // body 카테고리 탈출.
	xml.OutOfElem();               // response 카테고리 탈출.
}

void Weather_information()
{
	CMarkup xml;                        // 미세먼지 xml파일
	CTime cTime = CTime::GetCurrentTime();      // 현재시간
	CString Address, Address_more;            // 주소 
	CString Weather;					// 날씨 특보 정보 
	CString strDate, strDate2;					// 날짜

												// 날짜 정보
	strDate.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay() - 1);
	strDate2.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());

	// 주소
	Weather = _T("http://newsky2.kma.go.kr/service/WetherSpcnwsInfoService/WeatherInformation");
	Address_more = _T("&numOfRows=1&pageSize=1&pageNo=1&startPage=1&stnId=108");

	// 총 들어가는 주소
	Address = Weather + _T("?serviceKey=") + SERVICEKEY_YJ + _T("&fromTmFc=") + strDate + _T("&toTmFc=") + strDate2 + Address_more;
	HRESULT res = URLDownloadToFile(NULL, Address, _T("Weather_info.XML"), 0, NULL);      // 주소에 들어가서 주소에 있는 내용 Fine_dust.XML 생성

	CString strFileName = _T("Weather_info.XML");

	if (xml.Load(strFileName) != true)      // Weather.XML 파일 로드
	{
		AfxMessageBox(_T("파일이 없습니다."));   // 실패하면 뜨는 메시지 박스
		return;
	}

	// rseponse 카테고리 안
	xml.FindElem(_T("response"));      // response 정보를 찾는다.
	xml.IntoElem();                  // response 안의 내용 확인.

									 // body 카테고리 안
	xml.FindElem(_T("body"));         // body 정보를 찾는다.
	xml.IntoElem();                  // response->body 안의 내용 확인

									 // items 카테고리 안
	xml.FindElem(_T("items"));       // items 정보를 찾는다.
	xml.IntoElem();                  // response -> body -> items 안의 내용 확인

									 // item 카테고리 안
	xml.FindElem(_T("item"));      // item 정보를 찾는다.
	xml.IntoElem();               // response -> body -> items -> item안의 내용 확인

	xml.FindElem(_T("t1"));      // seoul 지역 미세먼지
	Weahter_info = xml.GetData();
	weahter_length = Weahter_info.GetLength();

	xml.OutOfElem();               // item 카테고리 탈출.
	xml.OutOfElem();               // items 카테고리 탈출.
	xml.OutOfElem();               // body 카테고리 탈출.
	xml.OutOfElem();               // response 카테고리 탈출.
}

//특보 메시지 움직이는 함수
UINT Text_move(LPVOID arg)
{

	ThreadArg *pArg = (ThreadArg*)arg; //스레드 선언
	CClientDC dc(pArg->pWnd);
	while (1) //반복문 선언.
	{
		for (int i = width; i > (int)(-weahter_length*width*0.014); i = i - (int)(width*0.0015))
		{
			dc.TextOut(i, height - 18, Weahter_info); //특보 정보를 x좌표부터 출력
			Sleep(10);						//20ms 잠듦.
		}
		dc.SelectStockObject(WHITE_PEN);
		dc.Rectangle(0, height - 18, 2500, height);
	}
	return 0;
}

//중기예보 디스플레이 함수
void CARTHOUSEView::displaying_junggi(int x, int y, int region)
{
	CBitmap bitmap;
	BITMAP bmpinfo;
	CClientDC dc(this);
	CBitmap* obit = NULL;
	DongNeYeBo_City_Find(x, y);								// 동네예보
	Middle_Cloud_Find(Cloud_YeBo_Code[region]);				// 중기육상 정보조회
	Middle_temperature_Find(temperature_YeBo_Code[region]); // 중기온도 정보조회
	CString str;
	CTime cTime = CTime::GetCurrentTime();      // 현재시간
	int Day = 0;								// 요일변수
	Day = cTime.GetDayOfWeek() + 1;				// 1:일요일, 2:월요일 ~ 7:토요일

	CRect rect;
	GetClientRect(&rect); //클라이언트 크기를 얻는다.
	int temperature_x[6] = { rect.Width() / 2 + rect.Width() / 24, rect.Width() / 2 + rect.Width() * 3 / 24, rect.Width() / 2 + rect.Width() * 5 / 24, rect.Width() / 2 + rect.Width() * 7 / 24, rect.Width() / 2 + rect.Width() * 9 / 24, rect.Width() / 2 + rect.Width() * 11 / 24 };   // 요일
																																																																						  //int temperature_x[6] = { 350, 450, 550, 650, 750, 850 };   // 요일
	int Weather_OneWeek_TMN1[6];
	int Weather_OneWeek_TMX1[6];
	for (int i = 1; i < 6; i++) {
		Weather_OneWeek_TMN1[i] = Weather_OneWeek_TMN[i] - Weather_OneWeek_TMN[0];
		Weather_OneWeek_TMX1[i] = Weather_OneWeek_TMX[i] - Weather_OneWeek_TMX[0];
	}
	POINT points_TMN[] = { { temperature_x[0], (int)(rect.Height()*0.8) },{ temperature_x[1], (int)(-(Weather_OneWeek_TMN1[1] * 8) + rect.Height() * 0.8) },{ temperature_x[2], (int)(-(Weather_OneWeek_TMN1[2] * 8) + rect.Height() * 0.8) },{ temperature_x[3], (int)(-(Weather_OneWeek_TMN1[3] * 8) + rect.Height() * 0.8) }
	,{ temperature_x[4], (int)(-(Weather_OneWeek_TMN1[4] * 8) + rect.Height() * 0.8) },{ temperature_x[5], (int)(-(Weather_OneWeek_TMN1[5] * 8) + rect.Height() * 0.8) } };   // 최저기온좌표

	POINT points_TMX[] = { { temperature_x[0], (int)(rect.Height() * 0.6) },{ temperature_x[1], (int)(-(Weather_OneWeek_TMX1[1] * 8) + rect.Height() * 0.6) },{ temperature_x[2], (int)(-(Weather_OneWeek_TMX1[2] * 8) + rect.Height() * 0.6) },{ temperature_x[3], (int)(-(Weather_OneWeek_TMX1[3] * 8) + rect.Height() * 0.6) }
	,{ temperature_x[4], (int)(-(Weather_OneWeek_TMX1[4] * 8) + rect.Height() * 0.6) },{ temperature_x[5], (int)(-(Weather_OneWeek_TMX1[5] * 8) + rect.Height() * 0.6) } };   // 최고기온좌표


	bitmap.LoadBitmapW(IDB_BACK1); //배경화면 비트맵 로드.
	bitmap.GetBitmap(&bmpinfo);

	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc); //메모리 디바이스 컨텍스트 생성
	obit = dcmem.SelectObject(&bitmap);
	//배경 비트맵 출력.
	dc.StretchBlt((int)((float)rect.Width() / 2), 0, (int)((float)rect.Width() / 2), (int)((float)rect.Height()), &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

	// 온도 그래프 표시 
	CPen pen1(PS_SOLID, 1, RGB(255, 255, 255));
	dc.SelectObject(&pen1);
	dc.Polyline(points_TMN, 6);
	dc.Polyline(points_TMX, 6);
	dc.SetBkMode(TRANSPARENT);
	dc.SelectStockObject(WHITE_PEN);
	dc.SetTextColor(RGB(255, 255, 255));
	dcmem.SelectObject(obit);
	// 서울·인천·경기도(0), 강원도영서(1), 강원도영동(2), 대전·세종·충청남도(3), 충청북도(4), 광주·전라남도(5)
	// 전라북도(6), 대구·경상북도(7), 부산·울산·경상남도(8), 제주도(9)

	CFont font;
	font.CreateFont(rect.Height() / 100 * 5,                     // 글자높이
		(int)(rect.Width() / 100 * 1.5),                      // 글자너비
		0,                      // 출력각도
		0,                      // 기준 선에서의각도
		FW_HEAVY,              // 글자굵기
		FALSE,                  // Italic 적용여부
		FALSE,                  // 밑줄적용여부
		FALSE,                  // 취소선적용여부
		DEFAULT_CHARSET,       // 문자셋종류
		OUT_DEFAULT_PRECIS,    // 출력정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑정밀도
		DEFAULT_QUALITY,       // 출력문자품질
		DEFAULT_PITCH,         // 글꼴Pitch
		_T("굴림체")           // 글꼴
	);
	dc.SelectObject(font);

	// 도시 이름 표시
	switch (region)
	{
	case 0:
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 6 / 48), (int)((float)rect.Height() *0.05), _T("서울·인천·경기도"));
		break;
	case 1:
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 3.3 / 48), (int)((float)rect.Height() *0.05), _T("강원도영서"));
		break;
	case 2:
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 3.3 / 48), (int)((float)rect.Height() *0.05), _T("강원도영동"));
		break;
	case 3:
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 6.6 / 48), (int)((float)rect.Height() *0.05), _T("대전·세종·충청남도"));
		break;
	case 4:
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 2.8 / 48), (int)((float)rect.Height() *0.05), _T("충청북도"));
		break;
	case 5:
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 4 / 48), (int)((float)rect.Height() *0.05), _T("광주·전라남도"));
		break;
	case 6:
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 2.8 / 48), (int)((float)rect.Height() *0.05), _T("전라북도"));
		break;
	case 7:
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 4 / 48), (int)((float)rect.Height() *0.05), _T("대구·경상북도"));
		break;
	case 8:
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 6.6 / 48), (int)((float)rect.Height() *0.05), _T("부산·울산·경상남도"));
		break;
	case 9:
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 2.2 / 48), (int)((float)rect.Height() *0.05), _T("제주도"));
		break;
	}
	CFont font11;
	font11.CreateFont(20,                     // 글자높이
		10,                     // 글자너비
		0,                      // 출력각도
		0,                      // 기준 선에서의각도
		FW_HEAVY,              // 글자굵기
		FALSE,                  // Italic 적용여부
		FALSE,                  // 밑줄적용여부
		FALSE,                  // 취소선적용여부
		DEFAULT_CHARSET,       // 문자셋종류
		OUT_DEFAULT_PRECIS,    // 출력정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑정밀도
		DEFAULT_QUALITY,       // 출력문자품질
		DEFAULT_PITCH,         // 글꼴Pitch
		_T("굴림체")           // 글꼴
	);
	dc.SelectObject(font11);	// 폰트 선택
	dc.Ellipse(temperature_x[0] - 5, (int)(rect.Height()*0.8 - 5), temperature_x[0] + 5, (int)(rect.Height()*0.8 + 5));
	dc.Ellipse(temperature_x[0] - 5, (int)(rect.Height()*0.6 - 5), temperature_x[0] + 5, (int)(rect.Height()*0.6 + 5));

	str.Format(_T("%d"), Weather_OneWeek_TMN[0]);
	dc.TextOutW(temperature_x[0] - 8, (int)((double)rect.Height()*0.8 - 30), str + _T("°"));
	str.Format(_T("%d"), Weather_OneWeek_TMX[0]);
	dc.TextOutW(temperature_x[0] - 7, (int)((double)rect.Height()*0.6 - 30), str + _T("°"));

	for (int i = 1; i < 6; i++) {
		Weather_OneWeek_TMN1[i] = Weather_OneWeek_TMN[i] - Weather_OneWeek_TMN[0];
		Weather_OneWeek_TMX1[i] = Weather_OneWeek_TMX[i] - Weather_OneWeek_TMX[0];

		// 온도 표시
		str.Format(_T("%d"), Weather_OneWeek_TMN[i]);
		dc.TextOutW(temperature_x[i] - 7, (int)(-((double)Weather_OneWeek_TMN1[i] * 8) + (double)rect.Height()*0.8 - 30), str + _T("°"));
		str.Format(_T("%d"), Weather_OneWeek_TMX[i]);
		dc.TextOutW(temperature_x[i] - 7, (int)(-((double)Weather_OneWeek_TMX1[i] * 8) + (double)rect.Height()*0.6 - 30), str + _T("°"));

		// 각 포인트 표시
		dc.Ellipse(temperature_x[i] - 5, (int)(-(Weather_OneWeek_TMN1[i] * 8) + rect.Height()*0.8 - 5), temperature_x[i] + 5, (int)(-(Weather_OneWeek_TMN1[i] * 8) + rect.Height()*0.8 + 5));
		dc.Ellipse(temperature_x[i] - 5, (int)(-(Weather_OneWeek_TMX1[i] * 8) + rect.Height()*0.6 - 5), temperature_x[i] + 5, (int)(-(Weather_OneWeek_TMX1[i] * 8) + rect.Height()*0.6 + 5));

	}

	for (int i = 0; i<6; i++)
	{
		// 요일표시
		switch (Day)
		{
		case 1:
			dc.TextOutW(temperature_x[i] - 8, (int)((float)rect.Height() *0.2), _T("일"));
			break;
		case 2:
			dc.TextOutW(temperature_x[i] - 8, (int)((float)rect.Height() *0.2), _T("월"));
			break;
		case 3:
			dc.TextOutW(temperature_x[i] - 8, (int)((float)rect.Height() *0.2), _T("화"));
			break;
		case 4:
			dc.TextOutW(temperature_x[i] - 8, (int)((float)rect.Height() *0.2), _T("수"));
			break;
		case 5:
			dc.TextOutW(temperature_x[i] - 8, (int)((float)rect.Height() *0.2), _T("목"));
			break;
		case 6:
			dc.TextOutW(temperature_x[i] - 8, (int)((float)rect.Height() *0.2), _T("금"));
			break;
		case 7:
			dc.TextOutW(temperature_x[i] - 8, (int)((float)rect.Height() *0.2), _T("토"));
			break;
		}

		// 요일사이간격
		dc.MoveTo((temperature_x[i] + temperature_x[i + 1]) / 2, (int)((float)rect.Height() *0.15));
		dc.LineTo((temperature_x[i] + temperature_x[i + 1]) / 2, (int)((float)rect.Height()*0.97));

		// 그림사이
		dc.MoveTo(temperature_x[i] + 40, (int)((float)rect.Height() *0.3));
		dc.LineTo((int)(temperature_x[i] - rect.Width()*1.5 / 48), (int)((float)rect.Height() *0.4) + 30);

		// 요일 증가
		Day = (Day % 7) + 1;

		// 구름상태 비트맵 출력.
		CBitmap bitmap;
		if (Weather_OneWeek_Am_SKY[i] == _T("맑음")) { //만약 오전 하늘 상태가 맑음이면
			HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
			bmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); //맑음 비트맵 로드.
			dcmem.CreateCompatibleDC(&dc);
			old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
			GetObject(bmp, sizeof(BITMAP), &bmpinfo);
			TransparentBlt(dc.m_hDC, (int)(temperature_x[i] - rect.Width()*1.5 / 48), (int)((float)rect.Height()*0.3), (int)((float)bmpinfo.bmWidth / 2.5), (int)((float)bmpinfo.bmHeight / 2.5),
				dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140)); //RGB(140,140,140)에 해당하는 픽셀을 투명으로 하여 bmp 출력
			dcmem.DeleteDC(); //삭제

		}
		else if (Weather_OneWeek_Am_SKY[i] == _T("구름조금")) {
			HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
			bmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3));
			dcmem.CreateCompatibleDC(&dc);
			old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
			GetObject(bmp, sizeof(BITMAP), &bmpinfo);
			TransparentBlt(dc.m_hDC, (int)(temperature_x[i] - rect.Width()*1.5 / 48), (int)((float)rect.Height()*0.3), (int)((float)bmpinfo.bmWidth / 2.5), (int)((float)bmpinfo.bmHeight / 2.5),
				dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
			dcmem.DeleteDC();
		}
		else if (Weather_OneWeek_Am_SKY[i] == _T("구름많음")) {
			HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
			bmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4));
			dcmem.CreateCompatibleDC(&dc);
			old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
			GetObject(bmp, sizeof(BITMAP), &bmpinfo);
			TransparentBlt(dc.m_hDC, (int)(temperature_x[i] - rect.Width()*1.5 / 48), (int)((float)rect.Height()*0.3), (int)((float)bmpinfo.bmWidth / 2.5), (int)((float)bmpinfo.bmHeight / 2.5),
				dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
			dcmem.DeleteDC();
		}
		else {
			HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
			bmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5));
			dcmem.CreateCompatibleDC(&dc);
			old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
			GetObject(bmp, sizeof(BITMAP), &bmpinfo);
			TransparentBlt(dc.m_hDC, (int)(temperature_x[i] - rect.Width()*1.5 / 48), (int)((float)rect.Height()*0.3), (int)((float)bmpinfo.bmWidth / 2.5), (int)((float)bmpinfo.bmHeight / 2.5),
				dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
			dcmem.DeleteDC();
		}

		CBitmap bitmap1;
		if (Weather_OneWeek_Pm_SKY[i] == _T("맑음")) {
			HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
			bmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2));
			dcmem.CreateCompatibleDC(&dc);
			old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
			GetObject(bmp, sizeof(BITMAP), &bmpinfo);
			TransparentBlt(dc.m_hDC, temperature_x[i] + rect.Width() / 200, (int)((float)rect.Height()*0.39), (int)((float)bmpinfo.bmWidth / 2.5), (int)((float)bmpinfo.bmHeight / 2.5),
				dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
			dcmem.DeleteDC();
		}
		else if (Weather_OneWeek_Pm_SKY[i] == _T("구름조금")) {
			HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
			bmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3));
			dcmem.CreateCompatibleDC(&dc);
			old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
			GetObject(bmp, sizeof(BITMAP), &bmpinfo);
			TransparentBlt(dc.m_hDC, temperature_x[i] + rect.Width() / 200, (int)((float)rect.Height()*0.39), (int)((float)bmpinfo.bmWidth / 2.5), (int)((float)bmpinfo.bmHeight / 2.5),
				dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
			dcmem.DeleteDC();
		}
		else if (Weather_OneWeek_Pm_SKY[i] == _T("구름많음")) {
			HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
			bmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4));
			dcmem.CreateCompatibleDC(&dc);
			old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
			GetObject(bmp, sizeof(BITMAP), &bmpinfo);
			TransparentBlt(dc.m_hDC, temperature_x[i] + rect.Width() / 200, (int)((float)rect.Height()*0.39), (int)((float)bmpinfo.bmWidth / 2.5), (int)((float)bmpinfo.bmHeight / 2.5),
				dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
			dcmem.DeleteDC();
		}
		else {
			HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
			bmp = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5));
			dcmem.CreateCompatibleDC(&dc);
			old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
			GetObject(bmp, sizeof(BITMAP), &bmpinfo);
			TransparentBlt(dc.m_hDC, temperature_x[i] + rect.Width() / 200, (int)((float)rect.Height()*0.39), (int)((float)bmpinfo.bmWidth / 2.5), (int)((float)bmpinfo.bmHeight / 2.5),
				dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
			dcmem.DeleteDC();
		}
	}
}

//초기화면 전국지도에 구름상태와 온도 출력.  
void CARTHOUSEView::city_cloud_disp() {
	CClientDC dc(this);
	HBITMAP old; BITMAP bmpinfo; CDC dcmem; //bmp 출력 위한 설정
	CString tmpstr; CFont font_tmp;	int tmp;//온도 출력 위한 설정
	dc.SetBkMode(TRANSPARENT);				//글씨 배경 투명으로 설정
	dc.SelectStockObject(BLACK_PEN);		//
	dc.SetTextColor(RGB(0, 0, 0));			//검정색 선택
	font_tmp.CreateFont(
		(int)(rect_client.Height() * 0.02),	// 글자높이
		(int)(rect_client.Width() * 0.008),		// 글자너비
		0,								// 출력각도
		0,								// 기준 선에서의각도
		FW_NORMAL,						// 글자굵기
		FALSE,							// Italic 적용여부
		FALSE,							// 밑줄적용여부
		FALSE,							// 취소선적용여부
		DEFAULT_CHARSET,				// 문자셋종류
		OUT_DEFAULT_PRECIS,				// 출력정밀도
		CLIP_DEFAULT_PRECIS,			// 클리핑정밀도
		DEFAULT_QUALITY,				// 출력문자품질
		DEFAULT_PITCH,					// 글꼴Pitch
		_T("굴림체")					// 글꼴
	);
	dc.SelectObject(font_tmp);			// 폰트 선택

										//서울 출력
	HBITMAP bmp_su;
	switch (Representative_City_Cloud[0]) //서울의 구름상태의 변수 값에 따라 이미지 로드.
	{
	case(1): bmp_su = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_su = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_su = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_su = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_su = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_su = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_su = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_su);
	GetObject(bmp_su, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.16), (int)(rect_client.Height()*0.2), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140)); //회색을 투명처리하여 bmp 출력.
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[0]; //서울의 현재 온도 변수를 받는다.
	tmpstr.Format(_T("%d"), tmp);	//int 변수 tmp를 CString tmpstr에 넣는다.
	dc.TextOutW((int)(rect_client.Width() * 0.18), (int)(rect_client.Height()*0.3), tmpstr + _T("°")); //온도 출력.


																									   //경기 출력
	HBITMAP bmp_gg;
	switch (Representative_City_Cloud[1])
	{
	case(1): bmp_gg = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_gg = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_gg = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_gg = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_gg = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_gg = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_gg = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_gg);
	GetObject(bmp_gg, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.2), (int)(rect_client.Height()*0.2), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[1];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.22), (int)(rect_client.Height()*0.3), tmpstr + _T("°"));


	//인천 출력
	HBITMAP bmp_ic;
	switch (Representative_City_Cloud[2])
	{
	case(1): bmp_ic = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_ic = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_ic = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_ic = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_ic = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_ic = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_ic = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_ic);
	GetObject(bmp_ic, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.09), (int)(rect_client.Height()*0.18), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[2];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.11), (int)(rect_client.Height()*0.28), tmpstr + _T("°"));

	//강원 출력
	HBITMAP bmp_gw;
	switch (Representative_City_Cloud[3])
	{
	case(1): bmp_gw = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_gw = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_gw = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_gw = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_gw = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_gw = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_gw = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_gw);
	GetObject(bmp_gw, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.29), (int)(rect_client.Height()*0.14), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[3];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.31), (int)(rect_client.Height()*0.24), tmpstr + _T("°"));

	//대전 출력
	HBITMAP bmp_dj;
	switch (Representative_City_Cloud[4])
	{
	case(1): bmp_dj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_dj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_dj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_dj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_dj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_dj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_dj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_dj);
	GetObject(bmp_dj, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.2), (int)(rect_client.Height()*0.4), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[4];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.22), (int)(rect_client.Height()*0.5), tmpstr + _T("°"));

	//충남 출력
	HBITMAP bmp_cn;
	switch (Representative_City_Cloud[5])
	{
	case(1): bmp_cn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_cn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_cn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_cn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_cn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_cn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_cn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_cn);
	GetObject(bmp_cn, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.14), (int)(rect_client.Height()*0.37), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[5];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.16), (int)(rect_client.Height()*0.47), tmpstr + _T("°"));

	//충북 출력
	HBITMAP bmp_cb;
	switch (Representative_City_Cloud[6])
	{
	case(1): bmp_cb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_cb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_cb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_cb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_cb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_cb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_cb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_cb);
	GetObject(bmp_cb, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.23), (int)(rect_client.Height()*0.31), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[6];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.25), (int)(rect_client.Height()*0.41), tmpstr + _T("°"));

	//광주 출력
	HBITMAP bmp_gj;
	switch (Representative_City_Cloud[7])
	{
	case(1): bmp_gj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_gj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_gj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_gj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_gj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_gj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_gj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_gj);
	GetObject(bmp_gj, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.13), (int)(rect_client.Height()*0.6), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[7];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.15), (int)(rect_client.Height()*0.7), tmpstr + _T("°"));

	//전남 출력
	HBITMAP bmp_jn;
	switch (Representative_City_Cloud[8])
	{
	case(1): bmp_jn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_jn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_jn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_jn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_jn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_jn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_jn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_jn);
	GetObject(bmp_jn, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.15), (int)(rect_client.Height()*0.68), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[8];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.17), (int)(rect_client.Height()*0.78), tmpstr + _T("°"));

	//전북 출력
	HBITMAP bmp_jb;
	switch (Representative_City_Cloud[9])
	{
	case(1): bmp_jb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_jb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_jb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_jb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_jb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_jb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_jb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_jb);
	GetObject(bmp_jb, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.17), (int)(rect_client.Height()*0.51), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[9];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.19), (int)(rect_client.Height()*0.61), tmpstr + _T("°"));

	//대구 출력
	HBITMAP bmp_dg;
	switch (Representative_City_Cloud[10])
	{
	case(1): bmp_dg = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_dg = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_dg = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_dg = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_dg = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_dg = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_dg = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_dg);
	GetObject(bmp_dg, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.31), (int)(rect_client.Height()*0.47), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[10];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.33), (int)(rect_client.Height()*0.57), tmpstr + _T("°"));

	//울산 출력
	HBITMAP bmp_us;
	switch (Representative_City_Cloud[11])
	{
	case(1): bmp_us = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_us = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_us = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_us = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_us = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_us = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_us = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_us);
	GetObject(bmp_us, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.39), (int)(rect_client.Height()*0.53), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[11];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.41), (int)(rect_client.Height()*0.63), tmpstr + _T("°"));

	//경남 출력
	HBITMAP bmp_gn;
	switch (Representative_City_Cloud[12])
	{
	case(1): bmp_gn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_gn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_gn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_gn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_gn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_gn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_gn = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_gn);
	GetObject(bmp_gn, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.29), (int)(rect_client.Height()*0.59), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[12];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.31), (int)(rect_client.Height()*0.69), tmpstr + _T("°"));

	//경북 출력
	HBITMAP bmp_gb;
	switch (Representative_City_Cloud[13])
	{
	case(1): bmp_gb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_gb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_gb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_gb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_gb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_gb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_gb = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_gb);
	GetObject(bmp_gb, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.34), (int)(rect_client.Height()*0.38), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[13];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.36), (int)(rect_client.Height()*0.48), tmpstr + _T("°"));

	//부산 출력
	HBITMAP bmp_bs;
	switch (Representative_City_Cloud[14])
	{
	case(1): bmp_bs = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_bs = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_bs = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_bs = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_bs = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_bs = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_bs = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_bs);
	GetObject(bmp_bs, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.35), (int)(rect_client.Height()*0.62), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[14];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.37), (int)(rect_client.Height()*0.72), tmpstr + _T("°"));

	//제주 출력
	HBITMAP bmp_jj;
	switch (Representative_City_Cloud[15])
	{
	case(1): bmp_jj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2)); break;
	case(2): bmp_jj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3)); break;
	case(3): bmp_jj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP4)); break;
	case(4): bmp_jj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP5)); break;
	case(5): bmp_jj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP6)); break;
	case(6): bmp_jj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7)); break;
	default:bmp_jj = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8)); break;
	}
	dcmem.CreateCompatibleDC(&dc);
	old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp_jj);
	GetObject(bmp_jj, sizeof(BITMAP), &bmpinfo);
	TransparentBlt(dc.m_hDC, (int)(rect_client.Width() * 0.11), (int)(rect_client.Height()*0.85), (int)(rect_client.Width()*0.05), (int)(rect_client.Width()*0.05),
		dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(140, 140, 140));
	dcmem.DeleteDC();
	tmp = Representative_City_temperature[15];
	tmpstr.Format(_T("%d"), tmp);
	dc.TextOutW((int)(rect_client.Width() * 0.13), (int)(rect_client.Height()*0.95), tmpstr + _T("°"));
}

// 1분 간격으로 작업자 스레드 이용 파싱함수
UINT CARTHOUSEView::Weather_Renewal(LPVOID arg)
{
	while (1)
	{
		for (int i = 0; i < 32; i = i + 2) //모든 지역의 단기예보, 동네예보 파싱
		{
			DanGi_City_Find(Representative_City[i], Representative_City[i + 1]);
			DongNeYeBo_City_Find(Representative_City[i], Representative_City[i + 1]);
			Thread_num++;
		}
		Thread_num = 0;
		Weather_information();
		g_event.PulseEvent();	//신호 이벤트의 상태 (사용 가능)를 설정,
								//모든 대기 스레드를 해제로 설정
		Sleep(60000);   // 1분 잠듬
	}
	return 0;
}


//세부지역에 깃발을 그린다. 매개변수를 통해 깃발의 색과 크기 변경가능
void CARTHOUSEView::draw_flag(CPoint locate, bool color, int size)
{
	CClientDC dc(this);
	CBrush brush_B(RGB(0, 0, 0));
	CBrush brush_W(RGB(255, 255, 255)); //미선택시 하얀 깃발 출력을 위함
	CBrush brush_R(RGB(255, 0, 0)); //선택시 빨간 깃발 출력을 위함
	CBrush *pOldBrush = dc.SelectObject(&brush_B);
	CPoint pt(10, 10);
	float size_change; //size로 크기를 조정한다. n%만큼 크기를 더하게 된다.

	size_change = ((float)100 + (float)size) / (float)100;
	GetClientRect(&rect_client);
	dc.Rectangle((int)((float)locate.x / MAP_KO_RATIO_X*rect_client.Width() / 1000), (int)(locate.y / MAP_KO_RATIO_Y*rect_client.Height() / 1000), (int)((locate.x + (float)rect_client.Width()*0.008*size_change) / MAP_KO_RATIO_X*rect_client.Width() / 1000), (int)((locate.y + (float)rect_client.Height()*0.05*size_change) / MAP_KO_RATIO_Y*rect_client.Height() / 1000));
	dc.SelectObject(pOldBrush);
	if (color == FALSE) //color 이 FALSE 이면 흰색 깃발, TRUE 이면 빨간 깃발
	{
		CBrush *pOldBrush = dc.SelectObject(&brush_W);

	}
	else
	{
		CBrush *pOldBrush = dc.SelectObject(&brush_R);

	}
	dc.Rectangle((int)((locate.x + (float)rect_client.Width()*0.0064*size_change) / MAP_KO_RATIO_X*rect_client.Width() / 1000), (int)(locate.y / MAP_KO_RATIO_Y*rect_client.Height() / 1000), (int)((locate.x + (float)rect_client.Width()*0.03*size_change) / MAP_KO_RATIO_X*rect_client.Width() / 1000), (int)((locate.y + (float)rect_client.Height()*0.02*size_change) / MAP_KO_RATIO_Y*rect_client.Height() / 1000));
	dc.SelectObject(pOldBrush);
}

//마우스 클릭시 발생하는 point 의 위치를 리젼의 위치와 비교한다.
//마우스 클릭한 point 가 리전 안에 있을경우 선택된 리젼의 정보를 전역변수에 저장한다.
//선택된 리젼의 깃발을 빨강 깃발로 표시한다.
void CARTHOUSEView::PttoRg(int pt[], CPoint mpos, CString str[], int xy[])
{
	CClientDC dc(this);
	CPoint point;
	CRgn rgn;
	CRgn rgn_arr[20];
	int saved_x = 0, saved_y = 0, saved_region = 0;
	CString saved_name;
	GetClientRect(&rect_client);
	int size, i;
	for (size = 0;; size++)
	{
		if (pt[size] == 0)
			break;
	}

	for (i = 0; i < size; i += 2)
	{
		point.x = pt[i];
		point.y = pt[i + 1];

		rgn.CreateRectRgn((int)(pt[i] * rect_client.Width() / 1000 / MAP_KO_RATIO_X), (int)(pt[i + 1] * rect_client.Height() / 1000 / MAP_KO_RATIO_Y), (int)((pt[i] + 50) * rect_client.Width() / 1000 / MAP_KO_RATIO_X), (int)((pt[i + 1] + 50) * rect_client.Height() / 1000 / MAP_KO_RATIO_Y));
		if (rgn.PtInRegion(mpos))
		{

			draw_flag(point, TRUE);
			CString fff;
			saved_x = xy[i];
			saved_y = xy[i + 1];
			saved_region = pt[size + 1];
			saved_name = str[i / 2];
		}
		else {
			CPen pen1(PS_SOLID, 5, RGB(0, 255, 255));
			CPen *pOldPen = dc.SelectObject(&pen1);
			dc.SelectStockObject(NULL_BRUSH);
			draw_flag(point);
			dc.SetBkMode(TRANSPARENT);
			dc.TextOutW((int)(point.x + (float)rect_client.Width()*0.0064) / MAP_KO_RATIO_X*rect_client.Width() / 1000, (int)((point.y - 25) / MAP_KO_RATIO_Y*rect_client.Height() / 1000), str[i / 2]);
			dc.SelectObject(&pOldPen);
		}
		rgn.DeleteObject();
	}

	if (saved_x != 0)
	{
		region_disp(saved_x, saved_y, saved_region, saved_name);
	}
}

//지역 단기예보 출력 함수
void CARTHOUSEView::region_disp(int x, int y, int region, CString region_name)
{
	Invalidate(FALSE);
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
					   // 서울·인천·경기도(0), 강원도영서(1), 강원도영동(2), 대전·세종·충청남도(3), 충청북도(4), 광주·전라남도(5)
					   // 전라북도(6), 대구·경상북도(7), 부산·울산·경상남도(8), 제주도(9)
	DongNeYeBo_City_Find(x, y);									// 동네예보
	DanGi_City_Find(x, y);										// 초단기예보조회
	Middle_Cloud_Find(Cloud_YeBo_Code[region]);					// 중기육상 정보조회
	Middle_temperature_Find(temperature_YeBo_Code[region]);		// 중기온도 정보조회
	Fine_dust_Find();											// 미세먼지
	Ultrafine_dust_Find();										// 초미세먼지
	CString str;
	CTime cTime = CTime::GetCurrentTime();						// 현재시간
	int Day = 0;												// 요일변수
	Day = cTime.GetDayOfWeek();									// 1:일요일, 2:월요일 ~ 7:토요일

	CString DDay;
	DDay = _T("");
	if (Day == 1) DDay = _T("일요일 ");
	else if (Day == 2) DDay = _T("월요일 ");
	else if (Day == 3) DDay = _T("화요일 ");
	else if (Day == 4) DDay = _T("수요일 ");
	else if (Day == 5) DDay = _T("목요일 ");
	else if (Day == 6) DDay = _T("금요일 ");
	else DDay = _T("토요일 ");

	CString AM_PM;
	AM_PM = _T("");
	if (cTime.GetHour() < 12) AM_PM = _T("오전");
	else AM_PM = _T("오후");

	CRect rect;
	GetClientRect(&rect);

	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BACK1);
	BITMAP bmpinfo;
	bitmap.GetBitmap(&bmpinfo);
	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	dcmem.SelectObject(&bitmap);
	dc.StretchBlt((int)((float)rect.Width() / 2), 0, (int)((float)rect.Width() / 2), (int)((float)rect.Height() *0.9),
		&dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY); //배경 출력
	dc.SetBkMode(TRANSPARENT);
	dc.SelectStockObject(WHITE_PEN);
	dc.SetTextColor(RGB(255, 255, 255));
	CString strDate = _T(""), strTime = _T("");
	strDate.Format(_T("%2d월 %d일 "), cTime.GetMonth(), cTime.GetDay());
	if (cTime.GetHour() >= 12) strTime.Format(_T(" %02d:%02d"), cTime.GetHour() - 12, cTime.GetMinute());
	else strTime.Format(_T(" %02d:%02d"), cTime.GetHour(), cTime.GetMinute());

	CFont font;
	font.CreateFont((int)(rect.Height() / 20 * 0.9),                     // 글자높이
		(int)(rect.Width() / 90 * 0.9),                     // 글자너비
		0,                      // 출력각도
		0,                      // 기준 선에서의각도
		FW_NORMAL,              // 글자굵기
		FALSE,                  // Italic 적용여부
		FALSE,                  // 밑줄적용여부
		FALSE,                  // 취소선적용여부
		DEFAULT_CHARSET,       // 문자셋종류
		OUT_DEFAULT_PRECIS,    // 출력정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑정밀도
		DEFAULT_QUALITY,       // 출력문자품질
		DEFAULT_PITCH,         // 글꼴Pitch
		_T("굴림체")           // 글꼴
	);
	dc.SelectObject(font);
	dc.TextOutW((int)((float)rect.Width() * 2.95 / 4), (int)((float)rect.Height() *0.07), region_name); //지역명 출력
	dc.TextOutW((int)((float)rect.Width() * 2.58 / 4), (int)((float)rect.Height() *0.15),
		strDate + DDay + AM_PM + strTime); //날짜, 시간 출력

										   //날씨, 구름상태 gif로 출력.
	if (Weather_Value[5] == _T("0")) {
		if (Weather_Value[1] == _T("1")) { //맑음
			gif_city.Load(_T("gif_cloud1.gif"));
			gif_city.Draw(rect);
		}
		else if (Weather_Value[1] == _T("2")) { //구름조금
			gif_city.Load(_T("gif_cloud2.gif"));
			gif_city.Draw(rect);
		}
		else if (Weather_Value[1] == _T("3")) { //구름많음
			gif_city.Load(_T("gif_cloud3.gif"));
			gif_city.Draw(rect);
		}
		else {
			gif_city.Load(_T("gif_cloud4.gif")); //흐림
			gif_city.Draw(rect);
		}
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() *3.1 / 48), (int)((float)rect.Height() *0.45), _T("강수확률 | ") + Weather_Value[0] + _T(" %"));
		//강수확률 출력
	}
	else {
		if (Weather_Value[5] == _T("1")) {
			gif_city.Load(_T("gif_rain.gif"));
			gif_city.Draw(rect);
		}
		else if (Weather_Value[5] == _T("2")) {
			gif_city.Load(_T("gif_rainsnow.gif"));
			gif_city.Draw(rect);
		}
		else {
			gif_city.Load(_T("gif_snow.gif"));
			gif_city.Draw(rect);
		}
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() *1.4 / 48), (int)((float)rect.Height() *0.45), _T("강수량 | ") + Weather_Value[3] + _T(" mm"));
		//강수량 출력
	}



	dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() *1.3 / 48), (int)((float)rect.Height() *0.52), _T("습도 | ") + Weather_Value[4] + _T(" %"));

	CString strfine_dust = _T(""), strUltrafine_dust = _T("");
	strfine_dust.Format(_T("%d"), fine_dust[region]);
	strUltrafine_dust.Format(_T("%d"), Ultrafine_dust[region]);
	dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() *3.1 / 48), (int)((float)rect.Height() *0.62),
		_T("미세먼지 | (") + strfine_dust + _T("㎛/㎥)"));
	dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 3.9 / 48), (int)((float)rect.Height() *0.77),
		_T("초미세먼지 | (") + strUltrafine_dust + _T("㎛/㎥)"));

	CFont font3;
	font3.CreateFont((int)(rect.Height() / 20 * 0.6),                     // 글자높이
		(int)(rect.Width() / 90 * 0.6),                     // 글자너비
		0,                      // 출력각도
		0,                      // 기준 선에서의각도
		FW_NORMAL,              // 글자굵기
		FALSE,                  // Italic 적용여부
		FALSE,                  // 밑줄적용여부
		FALSE,                  // 취소선적용여부
		DEFAULT_CHARSET,       // 문자셋종류
		OUT_DEFAULT_PRECIS,    // 출력정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑정밀도
		DEFAULT_QUALITY,       // 출력문자품질
		DEFAULT_PITCH,         // 글꼴Pitch
		_T("굴림체")           // 글꼴
	);
	dc.SelectObject(font3);

	//미세먼지 출력.
	CBitmap bitmap3;
	if (fine_dust[region] <= 30) {
		HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
		bmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DUST4));
		dcmem.CreateCompatibleDC(&dc);
		old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
		GetObject(bmp, sizeof(BITMAP), &bmpinfo);
		TransparentBlt(dc.m_hDC, (int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 7 / 48),
			(int)((float)rect.Height()*0.60),
			bmpinfo.bmWidth*(int)((float)rect.Width()) / 1000, bmpinfo.bmHeight*(int)((float)rect.Height()) * 2 / 1000,
			dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
		dcmem.DeleteDC();
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 2.5 / 48), (int)((float)rect.Height() *0.68), _T("★ 미세먼지 매우 좋음 ★"));

	}
	else if (fine_dust[region] <= 80) {
		HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
		bmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DUST3));
		dcmem.CreateCompatibleDC(&dc);
		old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
		GetObject(bmp, sizeof(BITMAP), &bmpinfo);
		TransparentBlt(dc.m_hDC, (int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 7 / 48), (int)((float)rect.Height()*0.60),
			bmpinfo.bmWidth*(int)((float)rect.Width()) / 1000, bmpinfo.bmHeight*(int)((float)rect.Height()) * 2 / 1000,
			dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
		dcmem.DeleteDC();
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 2.5 / 48), (int)((float)rect.Height() *0.68), _T("★ 미세먼지      좋음 ★"));
	}
	else if (fine_dust[region] <= 150) {
		HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
		bmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DUST2));
		dcmem.CreateCompatibleDC(&dc);
		old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
		GetObject(bmp, sizeof(BITMAP), &bmpinfo);
		TransparentBlt(dc.m_hDC, (int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 7 / 48), (int)((float)rect.Height()*0.60),
			bmpinfo.bmWidth*(int)((float)rect.Width()) / 1000, bmpinfo.bmHeight*(int)((float)rect.Height()) * 2 / 1000,
			dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
		dcmem.DeleteDC();
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 2.5 / 48), (int)((float)rect.Height() *0.68), _T("★ 미세먼지      나쁨 ★"));

	}
	else {
		HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
		bmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DUST1));
		dcmem.CreateCompatibleDC(&dc);
		old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
		GetObject(bmp, sizeof(BITMAP), &bmpinfo);
		TransparentBlt(dc.m_hDC, (int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 7 / 48), (int)((float)rect.Height()*0.60),
			bmpinfo.bmWidth*(int)((float)rect.Width()) / 1000, bmpinfo.bmHeight*(int)((float)rect.Height()) * 2 / 1000,
			dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
		dcmem.DeleteDC();
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 2.5 / 48), (int)((float)rect.Height() *0.68), _T("★ 미세먼지 매우 나쁨 ★"));

	}

	//초미세먼지 출력
	CBitmap bitmap4;
	if (Ultrafine_dust[region] <= 15) {
		HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
		bmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DUST4));
		dcmem.CreateCompatibleDC(&dc);
		old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
		GetObject(bmp, sizeof(BITMAP), &bmpinfo);
		TransparentBlt(dc.m_hDC, (int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 7 / 48), (int)((float)rect.Height()*0.75),
			bmpinfo.bmWidth*(int)((float)rect.Width()) / 1000, bmpinfo.bmHeight*(int)((float)rect.Height()) * 2 / 1000,
			dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
		dcmem.DeleteDC();
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 2.8 / 48), (int)((float)rect.Height() *0.83), _T("★ 초미세먼지 매우 좋음 ★"));
	}
	else if (Ultrafine_dust[region] <= 35) {
		HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
		bmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DUST3));
		dcmem.CreateCompatibleDC(&dc);
		old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
		GetObject(bmp, sizeof(BITMAP), &bmpinfo);
		TransparentBlt(dc.m_hDC, (int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 7 / 48), (int)((float)rect.Height()*0.75),
			bmpinfo.bmWidth*(int)((float)rect.Width()) / 1000, bmpinfo.bmHeight*(int)((float)rect.Height()) * 2 / 1000,
			dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
		dcmem.DeleteDC();
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 2.8 / 48), (int)((float)rect.Height() *0.83), _T("★ 초미세먼지      좋음 ★"));
	}
	else if (Ultrafine_dust[region] <= 75) {
		HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
		bmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DUST2));
		dcmem.CreateCompatibleDC(&dc);
		old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
		GetObject(bmp, sizeof(BITMAP), &bmpinfo);
		TransparentBlt(dc.m_hDC, (int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 7 / 48), (int)((float)rect.Height()*0.75),
			bmpinfo.bmWidth*(int)((float)rect.Width()) / 1000, bmpinfo.bmHeight*(int)((float)rect.Height()) * 2 / 1000,
			dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
		dcmem.DeleteDC();
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 2.8 / 48), (int)((float)rect.Height() *0.83), _T("★ 초미세먼지      나쁨 ★"));

	}
	else {
		HBITMAP old; HBITMAP bmp; BITMAP bmpinfo; CDC dcmem;
		bmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DUST1));
		dcmem.CreateCompatibleDC(&dc);
		old = (HBITMAP)SelectObject(dcmem.m_hDC, bmp);
		GetObject(bmp, sizeof(BITMAP), &bmpinfo);
		TransparentBlt(dc.m_hDC, (int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 7 / 48), (int)((float)rect.Height()*0.75),
			bmpinfo.bmWidth*(int)((float)rect.Width()) / 1000, bmpinfo.bmHeight*(int)((float)rect.Height()) * 2 / 1000,
			dcmem.m_hDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(255, 255, 255));
		dcmem.DeleteDC();
		dc.TextOutW((int)((float)rect.Width() * 3 / 4) - (int)((float)rect.Width() * 2.8 / 48), (int)((float)rect.Height() *0.83), _T("★ 초미세먼지 매우 나쁨 ★"));

	}

	//온도 출력
	CFont font2;
	font2.CreateFont(rect.Height() / 20 * 3,                     // 글자높이
		rect.Width() / 90 * 3,                     // 글자너비
		0,                      // 출력각도
		0,                      // 기준 선에서의각도
		FW_NORMAL,              // 글자굵기
		FALSE,                  // Italic 적용여부
		FALSE,                  // 밑줄적용여부
		FALSE,                  // 취소선적용여부
		DEFAULT_CHARSET,       // 문자셋종류
		OUT_DEFAULT_PRECIS,    // 출력정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑정밀도
		DEFAULT_QUALITY,       // 출력문자품질
		DEFAULT_PITCH,         // 글꼴Pitch
		_T("굴림체")           // 글꼴
	);
	dc.SelectObject(font2);

	int WV = CStringToint(Weather_Value[2]);
	CString strWV = _T(" ");
	strWV.Format(_T("%d"), WV);
	dc.TextOutW((int)((float)rect.Width() * 3 / 4) + (int)((float)rect.Width() * 2 / 48), (int)((float)rect.Height() *0.25), strWV + _T("°"));



}
//초기화면지도 출력 함수, 매개변수를 하나 받는데 같은 비트맵을 다른크기, 다른위치로 2번 출력함으로 이를 구분하기 위함
void CARTHOUSEView::map_disp(int mode)
{
	CClientDC dc(this);
	CBitmap* oldbit = NULL;
	CDC dcmem;
	CBitmap bm_ko;
	BITMAP bmpinfo;
	CRect rect_client;

	GetClientRect(&rect_client);

	bm_ko.LoadBitmapW(IDB_KO);

	bm_ko.GetBitmap(&bmpinfo);
	dcmem.CreateCompatibleDC(&dc);
	oldbit = dcmem.SelectObject(&bm_ko);
	if (mode == 0)
		dc.StretchBlt(0, 0, rect_client.Width() / MAP_KO_RATIO_X, rect_client.Height() / MAP_KO_RATIO_Y, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
	else if (mode == 1)
		dc.StretchBlt(0, (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), (int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.1), &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
	dcmem.SelectObject(oldbit);
	bm_ko.DeleteObject();
}


/*////////////////////////////////////////////////////////////////////////////////










함수 선언 종료













*//////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CARTHOUSEView, CFormView)

BEGIN_MESSAGE_MAP(CARTHOUSEView, CFormView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CARTHOUSEView 생성/소멸

CARTHOUSEView::CARTHOUSEView()
	: CFormView(IDD_ARTHOUSE_FORM)
{
}

CARTHOUSEView::~CARTHOUSEView()
{
}

void CARTHOUSEView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BS, gif_bs);
	DDX_Control(pDX, IDC_CB, gif_cb);
	DDX_Control(pDX, IDC_CN, gif_cn);
	DDX_Control(pDX, IDC_DG, gif_dg);
	DDX_Control(pDX, IDC_DJ, gif_dj);
	DDX_Control(pDX, IDC_GB, gif_gb);
	DDX_Control(pDX, IDC_GJ, gif_gj);
	DDX_Control(pDX, IDC_GN, gif_gn);
	DDX_Control(pDX, IDC_GW, gif_gw);
	DDX_Control(pDX, IDC_IC, gif_ic);
	DDX_Control(pDX, IDC_JB, gif_jb);
	DDX_Control(pDX, IDC_JJ, gif_jj);
	DDX_Control(pDX, IDC_JN, gif_jn);
	DDX_Control(pDX, IDC_SU, gif_su);
	DDX_Control(pDX, IDC_US, gif_us);
	DDX_Control(pDX, IDC_GG, gif_gg);
	DDX_Control(pDX, IDC_CITY, gif_city);
}

BOOL CARTHOUSEView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);
	return TRUE;
}

void CARTHOUSEView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}


// CARTHOUSEView 진단
#ifdef _DEBUG
void CARTHOUSEView::AssertValid() const
{
	CFormView::AssertValid();
}

void CARTHOUSEView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CARTHOUSEDoc* CARTHOUSEView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CARTHOUSEDoc)));
	return (CARTHOUSEDoc*)m_pDocument;
}
#endif //_DEBUG

// CARTHOUSEView 메시지 처리기
int CARTHOUSEView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CWinThread *p1 = NULL;
	p1 = AfxBeginThread(Weather_Renewal, this);

	g_event.Lock();
	CWinApp *pApp = AfxGetApp();
	mode=pApp->GetProfileIntW(_T("모드"), _T("mode"), mode);
	return 0;
}

void CARTHOUSEView::OnPaint()
{
	BITMAP bmpinfo;
	CBitmap bm_region;
	CDC dcmem0;
	CBitmap* oldbit = NULL;
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	GetClientRect(&rect_client);
	width = rect_client.Width();
	height = rect_client.Height();

	//onpaint 가 실행될때마다 리젼을 제거함으로 메모리 릭을 방지한다
	rgn_gb.DeleteObject();	rgn_gn.DeleteObject();	rgn_bs.DeleteObject();	rgn_us.DeleteObject();
	rgn_jn.DeleteObject();	rgn_jb.DeleteObject();	rgn_gj.DeleteObject();	rgn_jj.DeleteObject();
	rgn_cb.DeleteObject();	rgn_cn.DeleteObject();	rgn_dj.DeleteObject();	rgn_dg.DeleteObject();
	rgn_ic.DeleteObject();	rgn_su.DeleteObject();	rgn_gg.DeleteObject();	rgn_gw.DeleteObject();
	rgn_back.DeleteObject();

	//부산 리전
	rgn_bs.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.676), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.624), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.830), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.697));
	//광주
	rgn_gj.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.266), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.636), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.359), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.673));
	//대전
	rgn_dj.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.399), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.423), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.474), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.472));
	//대구
	rgn_dg.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.641), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.513), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.716), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.571));
	//서울
	rgn_su.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.310), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.220), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.397), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.257));
	//제주도
	rgn_jj.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.160), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.854), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.355), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.930));
	//인천
	rgn_ic.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.188), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.179), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.319), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.264));
	//강원도
	rgn_gw.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.501), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.081), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.836), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.312));
	//충남
	rgn_cn.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.244), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.492), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.508), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.622));
	//울산
	rgn_us.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.783), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.556), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.883), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.628));
	//전남
	rgn_jn.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.111), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.617), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.517), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.840));
	//경남
	rgn_gn.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.510), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.534), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.856), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.754));
	//전북
	rgn_jb.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.142), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.342), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.481), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.487));
	//경기도
	rgn_gg.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.168), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.124), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.485), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.333));
	//충북
	rgn_cb.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.466), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.310), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.658), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.5));
	//경북
	rgn_gb.CreateRectRgn((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.537), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.315), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.900), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.550));
	//뒤로가기 버튼
	rgn_back.CreateRectRgn(0, (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), (int)(rect_client.Width() / MAP_KO_RATIO_X * 0.1), (int)(rect_client.Height() / MAP_KO_RATIO_Y));

	//mode0 일때는 남한 지도를 출력한다
	if (mode == mode0_nosel || mode == mode0_sel) {
		map_disp(0);		//초기화면 출력.
		gif_city.UnLoad(); //출력 중인 gif 재생 멈추고 로드 해제, 화면에서 사라진다.
		city_cloud_disp(); //전국 지도에서 구름, 온도를 출력한다.
	}

	//mode0에서 특정 리전을 더블클릭하면 mode_00_nosel로 모드가 변경되고 해당 모드에 맞는 지도를 출력한다
	else if (mode > mode0_sel)
	{
		map_disp(1);
		if (mode == mode_bs_nosel || mode == mode_bs_sel)
		{
			bm_region.LoadBitmapW(IDB_BS);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_bs_nosel)
				PttoRg(pt_bs, pt_zero, str_bs, xy_bs);
		}

		else if (mode == mode_gj_nosel || mode == mode_gj_sel)
		{
			bm_region.LoadBitmapW(IDB_GJ);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_gj_nosel)
				PttoRg(pt_gj, pt_zero, str_gj, xy_gj);
		}

		else if (mode == mode_dj_nosel || mode == mode_dj_sel)
		{
			bm_region.LoadBitmapW(IDB_DJ);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_dj_nosel)
				PttoRg(pt_dj, pt_zero, str_dj, xy_dj);
		}

		else if (mode == mode_dg_nosel || mode == mode_dg_sel)
		{
			bm_region.LoadBitmapW(IDB_DG);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_dg_nosel)
				PttoRg(pt_dg, pt_zero, str_dg, xy_dg);
		}

		else if (mode == mode_su_nosel || mode == mode_su_sel)
		{
			bm_region.LoadBitmapW(IDB_SU);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_su_nosel)
				PttoRg(pt_su, pt_zero, str_su, xy_su);
		}

		else if (mode == mode_jj_nosel || mode == mode_jj_sel)
		{
			bm_region.LoadBitmapW(IDB_JJ);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_jj_nosel)
				PttoRg(pt_jj, pt_zero, str_jj, xy_jj);
		}

		else if (mode == mode_ic_nosel || mode == mode_ic_sel)
		{
			bm_region.LoadBitmapW(IDB_IC);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_ic_nosel)
				PttoRg(pt_ic, pt_zero, str_ic, xy_ic);
		}

		else if (mode == mode_gw_nosel || mode == mode_gw_sel)
		{
			bm_region.LoadBitmapW(IDB_GW);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_gw_nosel)
				PttoRg(pt_gw, pt_zero, str_gw, xy_gw);
		}

		else if (mode == mode_cn_nosel || mode == mode_cn_sel)
		{
			bm_region.LoadBitmapW(IDB_CN);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_cn_nosel)
				PttoRg(pt_cn, pt_zero, str_cn, xy_cn);
		}

		else if (mode == mode_us_nosel || mode == mode_us_sel)
		{
			bm_region.LoadBitmapW(IDB_US);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_us_nosel)
				PttoRg(pt_us, pt_zero, str_us, xy_us);
		}

		else if (mode == mode_jn_nosel || mode == mode_jn_sel)
		{
			bm_region.LoadBitmapW(IDB_JN);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_jn_nosel)
				PttoRg(pt_jn, pt_zero, str_jn, xy_jn);
		}

		else if (mode == mode_gn_nosel || mode == mode_gn_sel)
		{
			bm_region.LoadBitmapW(IDB_GN);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_gn_nosel)
				PttoRg(pt_gn, pt_zero, str_gn, xy_gn);
		}

		else if (mode == mode_jb_nosel || mode == mode_jb_sel)
		{
			bm_region.LoadBitmapW(IDB_JB);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_jb_nosel)
				PttoRg(pt_jb, pt_zero, str_jb, xy_jb);
		}

		else if (mode == mode_gg_nosel || mode == mode_gg_sel)
		{
			bm_region.LoadBitmapW(IDB_GG);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_gg_nosel)
				PttoRg(pt_gg, pt_zero, str_gg, xy_gg);
		}

		else if (mode == mode_cb_nosel || mode == mode_cb_sel)
		{
			bm_region.LoadBitmapW(IDB_CB);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_cb_nosel)
				PttoRg(pt_cb, pt_zero, str_cb, xy_cb);
		}

		else if (mode == mode_gb_nosel || mode == mode_gb_sel)
		{
			bm_region.LoadBitmapW(IDB_GB);
			bm_region.GetBitmap(&bmpinfo);
			dcmem0.CreateCompatibleDC(&dc);
			oldbit = dcmem0.SelectObject(&bm_region);
			dc.StretchBlt((int)(rect_client.Width() / MAP_KO_RATIO_X*0.1), 0, (int)(rect_client.Width() / MAP_KO_RATIO_X*0.9), (int)(rect_client.Height() / MAP_KO_RATIO_Y*0.9), &dcmem0, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			dcmem0.SelectObject(oldbit);
			bm_region.DeleteObject();
			if (mode == mode_gb_nosel)
				PttoRg(pt_gb, pt_zero, str_gb, xy_gb);
		}
	}
}


void CARTHOUSEView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CFont font;
	font.CreatePointFont((int)(rect_client.Width() / MAP_KO_RATIO_X * 0.676*0.5), _T("Arial"));
	CFont *pOldFont = dc.SelectObject(&font);

	dc.SetBkMode(TRANSPARENT);
	dc.SelectStockObject(NULL_BRUSH);

	//mode0_nosel 에서 특정 리전의 범위 내에 마우스로 좌클릭을 하면 mode0_sel 로 모드가 변경되고
	//선택된 특정 리젼이 영역처리되며 해당 지역의 중기 예보가 표시된다.
	//특정 지역들의 리전 범위 밖의 범위를 클릭하면 mode0_nosel로 모드가 변경된다.
	//mode0_sel에서 다른 지역의 리전을 클릭하면 모드가 mode0_nosel로 바뀐후 바로 OnLButtonDown을 실행하여
	//선택된 리젼이 영역처리 되며 해당 지역의 중기 예보가 표시된다.

	//mode0에서 특정 지역 리전을 더블클릭하면 mode_00_nosel로 모드가 변경된다. 이상태에서 화면의 깃발을 클릭하면
	//깃발이 빨간색으로 변하면서 해당 지역의 단기예보가 표시된다.
	if (mode == mode0_nosel)
	{
		mode = mode0_sel;
		if (rgn_bs.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.676), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.624), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.830), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.697));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.676), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.624), _T("부산"));
			displaying_junggi(97, 75, 8);
		}
		else if (rgn_gj.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.266), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.636), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.359), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.673));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.266), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.636), _T("광주"));
			displaying_junggi(59, 73, 5);
		}
		else if (rgn_dj.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.399), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.423), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.474), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.472));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.399), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.423), _T("대전"));
			displaying_junggi(57, 103, 3);
		}
		else if (rgn_dg.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.641), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.513), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.716), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.571));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.641), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.513), _T("대구"));
			displaying_junggi(89, 91, 7);
		}
		else if (rgn_su.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.310), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.220), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.397), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.257));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.310), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.220), _T("서울"));
			displaying_junggi(60, 126, 0);
		}
		else if (rgn_jj.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.160), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.854), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.355), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.930));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.160), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.854), _T("제주"));
			displaying_junggi(53, 38, 9);
		}
		else if (rgn_ic.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.188), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.179), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.319), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.264));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.188), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.179), _T("인천"));
			displaying_junggi(60, 126, 0);
		}
		else if (rgn_gw.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.501), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.081), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.836), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.312));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.501), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.081), _T("강원"));
			displaying_junggi(75, 130, 1);
		}
		else if (rgn_cn.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.244), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.492), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.508), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.622));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.244), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.492), _T("전북"));
			displaying_junggi(97, 75, 6);
		}
		else if (rgn_us.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.783), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.556), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.883), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.628));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.783), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.556), _T("울산"));
			displaying_junggi(59, 73, 8);
		}
		else if (rgn_jn.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.111), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.617), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.517), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.840));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.111), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.617), _T("전남"));
			displaying_junggi(59, 73, 5);
		}
		else if (rgn_gn.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.510), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.534), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.856), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.754));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.510), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.534), _T("경남"));
			displaying_junggi(97, 15, 8);
		}
		else if (rgn_jb.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.142), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.342), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.481), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.487));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.142), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.342), _T("충남"));
			displaying_junggi(63, 89, 3);
		}
		else if (rgn_gg.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.168), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.124), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.485), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.333));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.168), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.124), _T("경기"));
			displaying_junggi(60, 126, 0);
		}
		else if (rgn_cb.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.415), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.300), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.650), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.500));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.415), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.300), _T("충북"));
			displaying_junggi(74, 111, 4);
		}
		else if (rgn_gb.PtInRegion(point))
		{
			dc.Rectangle((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.537), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.315), (int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.900), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.550));
			dc.TextOutW((int)((float)rect_client.Width() / MAP_KO_RATIO_X * 0.537), (int)((float)rect_client.Height() / MAP_KO_RATIO_Y * 0.315), _T("경북"));
			displaying_junggi(89, 71, 7);
		}
		else
			mode = mode0_nosel;
	}

	else if (mode == mode0_sel)
	{
		mode = mode0_nosel;
		RedrawWindow();
		OnLButtonDown(nFlags, mpos1);
	}

	else if (mode > mode0_sel)
	{
		if (mode % 2 == 0)
			//	mode++;
			switch (mode / 2)
			{
			case 1: PttoRg(pt_bs, point, str_bs, xy_bs); break;
			case 2: PttoRg(pt_gj, point, str_gj, xy_gj); break;
			case 3: PttoRg(pt_dj, point, str_dj, xy_dj); break;
			case 4: PttoRg(pt_dg, point, str_dg, xy_dg); break;
			case 5: PttoRg(pt_su, point, str_su, xy_su); break;
			case 6: PttoRg(pt_jj, point, str_jj, xy_jj); break;
			case 7: PttoRg(pt_ic, point, str_ic, xy_ic); break;
			case 8: PttoRg(pt_gw, point, str_gw, xy_gw); break;
			case 9: PttoRg(pt_cn, point, str_cn, xy_cn); break;
			case 10: PttoRg(pt_us, point, str_us, xy_us); break;
			case 11: PttoRg(pt_jn, point, str_jn, xy_jn); break;
			case 12: PttoRg(pt_gn, point, str_gn, xy_gn); break;
			case 13: PttoRg(pt_jb, point, str_jb, xy_jb); break;
			case 14: PttoRg(pt_gg, point, str_gg, xy_gg); break;
			case 15: PttoRg(pt_cb, point, str_cb, xy_cb); break;
			case 16: PttoRg(pt_gb, point, str_gb, xy_gb); break;
			default:break;
			}
	}
}


//mode0에서 특정 지역들의 리젼을 더블클릭하면 해당 지역의 지도가 표시되면서 mode_00_nosel로 변경된다.
//mode_00_nosel 에서 좌측 하단부의 작은 지도를 더블클릭하면 초기화면으로 돌아가고 mode0_nosel로 변경된다.
void CARTHOUSEView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	//Invalidate();
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (mode < mode_bs_nosel)
	{
		if (rgn_bs.PtInRegion(point))
			mode = mode_bs_nosel;

		else if (rgn_gj.PtInRegion(point))
			mode = mode_gj_nosel;

		else if (rgn_dj.PtInRegion(point))
			mode = mode_dj_nosel;

		else if (rgn_dg.PtInRegion(point))
			mode = mode_dg_nosel;

		else if (rgn_su.PtInRegion(point))
			mode = mode_su_nosel;

		else if (rgn_jj.PtInRegion(point))
			mode = mode_jj_nosel;

		else if (rgn_ic.PtInRegion(point))
			mode = mode_ic_nosel;

		else if (rgn_gw.PtInRegion(point))
			mode = mode_gw_nosel;

		else if (rgn_jb.PtInRegion(point))
			mode = mode_cn_nosel;

		else if (rgn_us.PtInRegion(point))
			mode = mode_us_nosel;

		else if (rgn_jn.PtInRegion(point))
			mode = mode_jn_nosel;

		else if (rgn_gn.PtInRegion(point))
			mode = mode_gn_nosel;

		else if (rgn_cn.PtInRegion(point))
			mode = mode_jb_nosel;

		else if (rgn_gg.PtInRegion(point))
			mode = mode_gg_nosel;

		else if (rgn_cb.PtInRegion(point))
			mode = mode_cb_nosel;

		else if (rgn_gb.PtInRegion(point))
			mode = mode_gb_nosel;

	}
	else if (rgn_back.PtInRegion(point) && mode>mode0_sel)
	{
		mode = mode0_nosel;

	}
	else return;
	CWinApp *pApp = AfxGetApp();
	pApp->WriteProfileInt(_T("모드"), _T("mode"), mode);
	RedrawWindow();
}

//마우스 좌표를 계속 받는다
void CARTHOUSEView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	mpos1.x = point.x;
	mpos1.y = point.y;
	CWnd::OnMouseMove(nFlags, point);
}

//마우스 우측버튼 클릭시 속보가 표시되는 스레드가 실행된다.
//한번더 클릭하면 스레드가 중지된다.
void CARTHOUSEView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	state_thread = !state_thread;

	arg1.pWnd = this;
	arg1.pos = 1;
	if (state_thread)
		pThread1 = AfxBeginThread(Text_move, &arg1);
	else
	{
		pThread1->SuspendThread();
		dc.SelectStockObject(NULL_PEN);
		dc.Rectangle(0, rect.Height() - 18, rect.Width(), rect.Height());
		CWnd::OnRButtonDown(nFlags, point);
	}
}



void CARTHOUSEView::OnSize(UINT nType, int cx, int cy)
{
	gif_city.UnLoad();			//창 크기가 변경되면 gif 재생을 멈추고 없앰.	
	RedrawWindow();				//ON_PAINT 메시지 호출, 화면 갱신
	CFormView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
