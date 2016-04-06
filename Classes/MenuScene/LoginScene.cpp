#include "LoginScene.h"
#include "RegisterScene.h"
#include "ShowGame.h"

#include "CustomUI/MButton.hpp"
#include "CustomUI/MLabel.hpp"
#include "CustomUI/MSprite.hpp"
#include "CustomUI/MEditBox.hpp"
#include "CustomUI/MLabel.hpp"
#include "CustomUI/MText.hpp"

#include "Config/GameConfig.h"

#include <protobufObject/login.pb.h>
#include <thread>

#include <iostream>
#include "DefaultSocket.h"

#if WIN32
#pragma comment(lib, "libprotobuf.lib")
#endif


#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <thread>

#include <string>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include "zlib.h"

#define MOD_GZIP_ZLIB_WINDOWSIZE 15
#define MOD_GZIP_ZLIB_CFACTOR    9
#define MOD_GZIP_ZLIB_BSIZE      8096
#define MAX_SIZE 1024 * 1024



#define TAG_BTN_FACEBOOK 1
#define TAG_BTN_LOGIN 2
#define TAG_BTN_REGISTER 3
#define TAG_BTN_PLAYNOW 4
#define TAG_BTN_FOGOTPASSWORD 5
#define TAG_EDITBOX_MATKHAU 6
#define TAG_EDITBOX_TAIKHOAN 7

using namespace cocos2d::ui;

Scene* LoginScene::createScene()
{
    
    auto scene = Scene::create();
   
    auto layer = LoginScene::create();

    scene->addChild(layer);

    return scene;
}

bool LoginScene::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    //BINLoginRequest *loginRequest = new BINLoginRequest();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float w = visibleSize.width;
    float h = visibleSize.height;
    
    
    auto bkg = MSprite::create(BKG_LOGIN,visibleSize);
    bkg->setPosition(origin.x, origin.y);
    
    
    //hotline
    auto hotline_txt = MLabel::create("Hotline : 19001755",25);
    hotline_txt->setPosition(Vec2(origin.x+15,origin.y+h-15-hotline_txt->getHeight()));
    
    
    //version
    auto version_txt = MLabel::create("Ver 1.0",25);
    version_txt->setPosition(Vec2(origin.x+w-version_txt->getWidth()-15,
                                  origin.y+h-15-version_txt->getHeight()));
    
    
    //girl
    auto girl = MSprite::create(SPRITE_GIRL_LOGIN);
    girl->setPosition(origin.x + visibleSize.width / 8, origin.y);
    
    
    //========================= buttons
    
    
    //loginfacebook Button
    auto btn_login_facebook = MButton::create(BTN_LOGIN_FACEBOOK,"Đăng nhập facebook",30,TAG_BTN_FACEBOOK);
    btn_login_facebook->setPosition(Vec2(w*0.95f-btn_login_facebook->getWidth(),h/3.0f));
    btn_login_facebook->setZoomScale(0.01f);
    btn_login_facebook->addTouchEventListener( CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    
    //đăng nhập
    auto btn_login = MButton::create(BTN_LOGIN,"Đăng nhập",30,TAG_BTN_LOGIN);
    btn_login->setPosition(Vec2(btn_login_facebook->getPosition().x,
                                btn_login_facebook->getPosition().y+btn_login_facebook->getHeight()-5));
    btn_login->addTouchEventListener( CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    
    //đăng ký
    auto btn_register = MButton::create(BTN_LOGIN,"Đăng ký",30,TAG_BTN_REGISTER);
    btn_register->setPosition(Vec2(btn_login_facebook->getPosition().x+btn_login_facebook->getWidth()/2
                                   -btn_register->getWidth()/2,
                                   btn_login->getPosition().y));
    btn_register->addTouchEventListener( CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    
    //choi ngay
    auto btn_playnow = MButton::create(BTN_LOGIN,"Chơi ngay",30,TAG_BTN_PLAYNOW);
    btn_playnow->setPosition(Vec2(btn_login_facebook->getPosition().x+btn_login_facebook->getWidth()
                                  -btn_playnow->getWidth(),
                                  btn_login->getPosition().y));
    btn_playnow->addTouchEventListener( CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    
    //quen mk
    auto fogotPassword = MButton::create("Quên mật khẩu?",25,TAG_BTN_FOGOTPASSWORD);
    fogotPassword->setPosition(Vec2(btn_login_facebook->getPosition().x+btn_login_facebook->getWidth()
                                    -fogotPassword->getWidth()-5,
                                btn_playnow->getPosition().y+btn_playnow->getHeight()+10));
    fogotPassword->addTouchEventListener( CC_CALLBACK_2(LoginScene::menuCallBack,this));
    
    
    //underline
    auto under_line = MText::create("______________",25);
    under_line->setPosition(Vec2(fogotPassword->getPosition().x,fogotPassword->getPosition().y));
    
    
    //========================= Text Field
    
    // Textfield mat khau
    auto background_matkhau = MSprite::create(BKG_INPUT_LOGIN);
    
    auto edit_matkhau = MEditBox::create(background_matkhau->getContentSize(),BKG_INPUT_LOGIN);
    edit_matkhau->setPosition(Vec2(btn_login_facebook->getPosition().x+10,
                                   fogotPassword->getPosition().y+fogotPassword->getHeight()+10));
    edit_matkhau->setPlaceHolder("  Nhập mật khẩu");
    edit_matkhau->setMaxLength(12);
    edit_matkhau->setTag(TAG_EDITBOX_MATKHAU);
    edit_matkhau->setInputFlag(EditBox::InputFlag::PASSWORD);
    edit_matkhau->setDelegate(this);
    
    
    // Textfield tai khoan
    
    auto edit_user = MEditBox::create(background_matkhau->getContentSize(),BKG_INPUT_LOGIN);
    edit_user->setPosition(Vec2(edit_matkhau->getPosition().x,
                                edit_matkhau->getPosition().y+background_matkhau->getHeight()+10));
    edit_user->setPlaceHolder("  Nhập tên");
    edit_user->setTag(TAG_EDITBOX_TAIKHOAN);
    edit_user->setMaxLength(12);
    edit_user->setDelegate(this);
    
    
    this->addChild(bkg);
    this->addChild(hotline_txt);
    this->addChild(version_txt);
    this->addChild(girl);
    
    
    this->addChild(btn_login_facebook);
    this->addChild(btn_login);
    this->addChild(btn_register);
    this->addChild(btn_playnow);
    this->addChild(fogotPassword);
    this->addChild(under_line);
    
    this->addChild(edit_matkhau);
    this->addChild(edit_user);
    
    //edit_matkhau->touchDownAction(NULL, cocos2d::ui::Widget::TouchEventType::ENDED);
    
    
    sprite = Sprite::create("bgr_textview.png");
    sprite->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY());
    this->addChild(sprite, 0);
    
    this->scheduleUpdate();
    
    
    return true;
}


bool loginSuccess = false;


void LoginScene::update(float delta){
    auto position = sprite->getPosition();
    position.x -= 250 * delta;
    if (position.x  < 0 - (sprite->getBoundingBox().size.width / 2))
        position.x = this->getBoundingBox().getMaxX() + sprite->getBoundingBox().size.width/2;
    sprite->setPosition(position);
    
    if(loginSuccess){
        auto showgame = RegisterScene::createScene();
        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.1f,showgame));
        loginSuccess = false;
    }
}


void callNetwork(char *ackBuf, int size) {
    DefaultSocket *defaultSocket = new DefaultSocket();
    bool isConnected = defaultSocket->connectSocket("192.168.1.50", 1240);
    //	CCLOG("already connected: %s", isConnected ? "true" : "false");
    // CCLOG("Send data: %s", loginRequest->SerializeAsString());
    defaultSocket->sendData(ackBuf, size);
    std::vector<char> bufferRead(500);
    defaultSocket->readData(bufferRead, 500);
    LoginScene::readFrom(bufferRead, 500);
    // defaultSocket->readData(bufferRead, 500);
    defaultSocket->closeSocket();
}

void testProtoLogin() {
    
    
    //23 bytes protobuf
    BINLoginRequest* loginRequest = new BINLoginRequest();
    loginRequest->set_username("sanglx");
    loginRequest->set_password("12345678");
    loginRequest->set_cp("0");
    loginRequest->set_appversion("1");
    loginRequest->set_clienttype(1);
    
    CCLOG("byte size: %d" , loginRequest->ByteSize());
    
    string myString = "hello";
    
    std::vector<char> bytes(myString.begin(), myString.end());
    bytes.push_back('\0');
    
    //N byte session
    char *session = &bytes[0];
    //2 byte lenSession
    int lenSession = strlen(session);
    int size = loginRequest->ByteSize() + 11 + lenSession;
    char* ackBuf = new char[size];
    // ArrayOutputStream os(ackBuf, size);
    google::protobuf::io::ArrayOutputStream arrayOut(ackBuf,size);
    google::protobuf::io::CodedOutputStream codedOut(&arrayOut);
    
    char* buf = new char[1];
    buf[0] = 2;
    codedOut.WriteRaw(buf, 1); //write os
    char* dataSize = new char[4];
    
    int data_size = loginRequest->ByteSize() + 4;
    dataSize[0] = (data_size >> 24) & 0xFF;
    dataSize[1] = (data_size >> 16) & 0xFF;
    dataSize[2] = (data_size >> 8) & 0xFF;
    dataSize[3] = (data_size >> 0) & 0xFF;
    codedOut.WriteRaw(dataSize, 4); //write data size
    char* char_len_session = new char[2];
    char_len_session[0] = (lenSession >> 8) & 0xFF;
    char_len_session[1] = (lenSession >> 0) & 0xFF;
    
    // std::string str_len_session = string(char_len_session);
    
    //2 byte length session
    codedOut.WriteRaw(char_len_session, 2);
    
    //n byte session
    codedOut.WriteRaw(session, lenSession);
    // loginRequest->SerializeToCodedStream(&codedOut);
    
    char* mid = new char[2];
    mid[0] = (1001 >> 8) & 0xFF;
    mid[1] = (1001 >> 0) & 0xFF;
    
    codedOut.WriteRaw(mid, 2);
    
    
    loginRequest->SerializeToCodedStream(&codedOut);
    
    string buffers = string(ackBuf);
    // string buffers = string((char*) ackBuf, codedOut.ByteCount());
    /*Base64 b64;
     std::string encoded = b64.base64_encode(reinterpret_cast<const unsigned char*>(ackBuf), strlen(ackBuf));*/
    
    // CCLOG("%s", bufff.c_str());
    
    //end of file
    char *eot = new char[2];
    eot[0] = '\r';
    eot[1] = '\n';
    
    codedOut.WriteRaw(eot, 2);
    thread *t = new thread(callNetwork, ackBuf, size);
    if(t->joinable())
        t->detach();
    // delete(ackBuf);
}

struct membuf : std::streambuf
{
    membuf(char* begin, char* end) {
        this->setg(begin, begin, end);
    }
};



void LoginScene::readFrom(std::vector<char> read_str, int len) {
    char* chars_from_read = &read_str[0];
    google::protobuf::io::ArrayInputStream arrayIn(chars_from_read, len);
    google::protobuf::io::CodedInputStream codedIn(&arrayIn);
    //read data size
    char *data_size_chars = new char[4];
    codedIn.ReadRaw(data_size_chars, 4);
    
    int bytes_size = ((data_size_chars[0] & 0xFF) << 24) + ((data_size_chars[1] & 0xFF) << 16) + ((data_size_chars[2] & 0xFF) << 8) + ((data_size_chars[3] & 0xFF) << 0);
    
    //read compress
    char *is_compress_chars = new char[1];
    codedIn.ReadRaw(is_compress_chars, 1);
    
    int is_compress = is_compress_chars[0];
    
    int left_byte_size = bytes_size - 1;
    
    string message;
    
    /*if is_compress = 1 */
    if (is_compress == 1) {
        google::protobuf::io::CodedInputStream::Limit msgLimit = codedIn.PushLimit(left_byte_size); //limit compressed size
        //read data compressed
        char *data_compressed = new char[left_byte_size];
        // test data
        // char test_data[] = {31,-117, 8, 0, 0, 0, 0, 0, 0, 0, 99, -32, 102, 126, -55, -63, 40, -60, -102, -101, 24, -97, -101, 8, 0, -41, 18, 51, -108, 13, 0, 0, 0};
        
        codedIn.ReadRaw(data_compressed, left_byte_size);
        codedIn.PopLimit(msgLimit);
        vector<char> result = LoginScene::decompress_gzip2(data_compressed, (uLong)left_byte_size);//decompress_gzip2(data_compressed, (uLong)left_byte_size);
        char* data_uncompressed = reinterpret_cast<char*>(result.data());
        
        int length = result.size();
        int index = 0;
        bool debug = false;
        while (index < length) {
            google::protobuf::Message *loginResponse;
            //read datablocksize
            int data_size_block = ((data_uncompressed[index] & 0xFF) << 8) + ((data_uncompressed[index + 1] & 0xFF) << 0);
            //read messageid
            int messageid = ((data_uncompressed[index + 2] & 0xFF) << 8) + ((data_uncompressed[index + 3] & 0xFF) << 0);
            loginResponse->ParseFromArray(&data_uncompressed[index + 4], data_size_block - 2);
            index += (data_size_block + 2);
            
            if (debug) break;
        }
    }
    else {
        
        /* if is_compression = 0 */
        while (left_byte_size > 0) {
            
            
            //read protobuf + data_size_block + mid
            
            //read datasizeblock
            char *data_size_block_chars = new char[2];
            
            codedIn.ReadRaw(data_size_block_chars, 2);
            
            int data_size_block = ((data_size_block_chars[0] & 0xFF) << 8) + ((data_size_block_chars[1] & 0xFF) << 0);
            
            // read messageid
            
            char *mid_chars = new char[2];
            
            codedIn.ReadRaw(mid_chars, 2);
            
            int messageid = ((mid_chars[0] & 0xFF) << 8) + ((mid_chars[1] & 0xFF) << 0);
            
            google::protobuf::io::CodedInputStream::Limit msgLimit = codedIn.PushLimit(data_size_block - 2);
            
            BINLoginResponse loginResponse;
            loginResponse.ParseFromCodedStream(&codedIn);
            
            //setLogin(loginResponse.responsecode());
            loginSuccess = loginResponse.responsecode();
            message = loginResponse.message();
            
            codedIn.PopLimit(msgLimit);
            left_byte_size -= (data_size_block + 2);
        }
    }
    
    if(loginSuccess) {
        //TODO: change scene
        
        
    } else {
        cocos2d::MessageBox(message.c_str(), "failed");
    }
}

//======================

std::string compress_gzip(const std::string& str,
                          int compressionlevel = Z_BEST_COMPRESSION)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));
    
    if (deflateInit2(&zs,
                     compressionlevel,
                     Z_DEFLATED,
                     MOD_GZIP_ZLIB_WINDOWSIZE + 16,
                     MOD_GZIP_ZLIB_CFACTOR,
                     Z_DEFAULT_STRATEGY) != Z_OK
        ) {
        throw(std::runtime_error("deflateInit2 failed while compressing."));
    }
    
    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();           // set the z_stream's input
    
    int ret;
    char outbuffer[32768];
    std::string outstring;
    
    // retrieve the compressed bytes blockwise
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);
        
        ret = deflate(&zs, Z_FINISH);
        
        if (outstring.size() < zs.total_out) {
            // append the block to the output string
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
    } while (ret == Z_OK);
    
    deflateEnd(&zs);
    
    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
        throw(std::runtime_error(oss.str()));
    }
    
    return outstring;
}

// Found this one here: http://panthema.net/2007/0328-ZLibString.html, author is Timo Bingmann
/** Compress a STL string using zlib with given compression level and return
 * the binary data. */
std::string compress_deflate(const std::string& str,
                             int compressionlevel = Z_BEST_COMPRESSION)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));
    
    if (deflateInit(&zs, compressionlevel) != Z_OK)
        throw(std::runtime_error("deflateInit failed while compressing."));
    
    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();           // set the z_stream's input
    
    int ret;
    char outbuffer[32768];
    std::string outstring;
    
    // retrieve the compressed bytes blockwise
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);
        
        ret = deflate(&zs, Z_FINISH);
        
        if (outstring.size() < zs.total_out) {
            // append the block to the output string
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
    } while (ret == Z_OK);
    
    deflateEnd(&zs);
    
    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
        throw(std::runtime_error(oss.str()));
    }
    
    return outstring;
}

/** Decompress an STL string using zlib and return the original data. */
std::string decompress_deflate(const std::string& str)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));
    
    if (inflateInit(&zs) != Z_OK)
        throw(std::runtime_error("inflateInit failed while decompressing."));
    
    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();
    
    int ret;
    char outbuffer[32768];
    std::string outstring;
    
    // get the decompressed bytes blockwise using repeated calls to inflate
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);
        
        ret = inflate(&zs, 0);
        
        if (outstring.size() < zs.total_out) {
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
        
    } while (ret == Z_OK);
    
    inflateEnd(&zs);
    
    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") "
        << zs.msg;
        throw(std::runtime_error(oss.str()));
    }
    
    return outstring;
}
vector<char> LoginScene::decompress_gzip2(const char* byte_arr, uLong length) {
    
    vector<char> result;
    vector<char> nil_vector;
    if (length == 0) return nil_vector;
    bool done = false;
    z_stream zs;
    memset(&zs, 0, sizeof(zs));
    
    zs.next_in = (Bytef*) byte_arr;
    zs.avail_in = length;
    zs.total_out = 0;
    zs.zalloc = Z_NULL;
    zs.zfree = Z_NULL;
    
    if (inflateInit2(&zs, MOD_GZIP_ZLIB_WINDOWSIZE + 16) != Z_OK)  return nil_vector;
    
    int ret;
    
    char outbuffer[32768];
    
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);
        
        ret = inflate(&zs, Z_SYNC_FLUSH);
        
        if (result.size() < zs.total_out) {
            int size = result.size();
            for (int i = 0; i < zs.total_out - size; i++)
                result.push_back(outbuffer[i]);
        }
        
    } while (ret == Z_OK);
    
    inflateEnd(&zs);
    
    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") "
        << zs.msg;
        return nil_vector;
    }
    return result;
}

std::string decompress_gzip(const std::string &str)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));
    
    if (inflateInit2(&zs, MOD_GZIP_ZLIB_WINDOWSIZE + 16) != Z_OK)
        throw(std::runtime_error("inflateInit failed while decompressing."));
    
    
    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();
    
    
    int ret;
    char outbuffer[32768];
    std::string outstring;
    
    
    
    // get the decompressed bytes blockwise using repeated calls to inflate
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);
        
        ret = inflate(&zs, 0);
        
        
        if (outstring.size() < zs.total_out) {
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
        
    } while (ret == Z_OK);
    
    inflateEnd(&zs);
    
    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") "
        << zs.msg;
        throw(std::runtime_error(oss.str()));
    }
    
    return outstring;
}


void LoginScene::menuCallBack(Ref *pSender, Widget::TouchEventType eventType){
    if(eventType == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*) pSender;
        int tag = button->getTag();
        switch (tag) {
            case TAG_BTN_FACEBOOK:
                CCLOG("%s","Login with facebook!");
                break;
            case TAG_BTN_LOGIN:
                CCLOG("%s","Login with esxit!");
                break;
            case TAG_BTN_REGISTER:
                {
                    auto registerscene = RegisterScene::createScene();
                    Director::getInstance()->replaceScene(TransitionMoveInR::create(0.25f, registerscene));
                    
                }
                break;
            case TAG_BTN_PLAYNOW:
                {
                    auto select = ShowGame::createScene();
                   Director::getInstance()->replaceScene(TransitionCrossFade::create(0.15f, select));
                }
                break;
            case TAG_BTN_FOGOTPASSWORD:
                CCLOG("%s","Forgot_Password!");
                break;
            default:
                break;
        }
    }

}

#pragma mark - EditBoxDelegate

void LoginScene::editBoxEditingDidBegin(EditBox *editBox) {
    CCLOG("%s","edit begin!");
}

void LoginScene::editBoxEditingDidEnd(EditBox *editBox) {
    
    CCLOG("%s","edit end!");
}

void LoginScene::editBoxTextChanged(EditBox *editBox, const std::string& text) {
    CCLOG("%s","edit changed!");
}

void LoginScene::editBoxReturn(EditBox *editBox) {
    switch (editBox->getTag()) {
        case TAG_EDITBOX_MATKHAU:
            this->password_str = editBox->getText();
            CCLOG("%s",this->password_str.c_str());
            break;
        case TAG_EDITBOX_TAIKHOAN:
            this->user_id_str = editBox->getText();
            CCLOG("%s",this->user_id_str.c_str());
            break;
        default:
            break;
    }
}


