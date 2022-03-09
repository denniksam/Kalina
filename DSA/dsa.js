function Dsa() {
    const I = this ;

    I.init = function() {
        // I.p = BigInt( "89884656743115796742429711405763364460177151692783429800884652449310979263752253529349195459823881715145796498046459238345428121561386626945679753956400077352882071663925459750500807018254028771490434021315691357123734637046894876123496168716251735252662742462099334802433058472377674408598573487858308054417") ;
        // I.q = BigInt( "1193447034984784682329306571139467195163334221569" ) ;
        I.p = BigInt( "0x86F5CA03DCFEB225063FF830A0C769B9DD9D6153AD91D7CE27F787C43278B447E6533B86B18BED6E8A48B784A14C252C5BE0DBF60B86D6385BD2F12FB763ED8873ABFD3F5BA2E0A8C0A59082EAC056935E529DAF7C610467899C77ADEDFC846C881870B7B19B2B58F9BE0521A17002E3BDD6B86685EE90B3D9A1B02B782B1779" ) ;
        I.q = BigInt( "0x996F967F6C8E388D9E28D01E205FBA957A5698B1" ) ;
        I.g = BigInt( "0x07B0F92546150B62514BB771E2A0C0CE387F03BDA6C56B505209FF25FD3C133D89BBCD97E904E09114D9A7DEFDEADFC9078EA544D2E401AEECC40BB9FBBF78FD87995A10A1C27CB7789B594BA7EFB5C4326A9FE59A070E136DB77175464ADCA417BE5DCE2F40D10A46A3A3943F26AB7FD9C0398FF8C76EE0A56826A8A88F1DBD" ) ;
    }
    
    I.pmod = function( x, p, m ) {
        if( p == 1n ) return x % m ;
        if( p % 2n == 1n ) return ( x * I.pmod( x, p - 1n, m ) ) % m ;
        const y = I.pmod( x, p / 2n, m )
        return ( y * y ) % m ; 
    }

    I.bigRand = function( bitlength ) {
        let ret = "0x" ;
        for(let i = 0; i < bitlength / 4; ++i ) {
            ret += "012334456789ABCDEF".charAt( Math.floor( Math.random() * 16 ) ) ;
        }
        return BigInt( ret ) ;
    }

    I.makePair = function( key ) {
        if( typeof key == 'string' )  key = BigInt( '0x' + key ) ; 
        if( typeof key != 'bigint' ) throw "makePair: Invalid key format (HEX string or bigint expected)" ;
        let ret = I.pmod( I.g, key, I.p ) ;
        return ret.toString( 16 ) ;
    }
    
    I.sign = function( hash, key ) {
        if( typeof hash == 'string' ) hash = BigInt( '0x' + hash ) ; 
        if( typeof hash != 'bigint' ) throw "sign: Invalid hash format (HEX string or bigint expected)" ;
        if( typeof key == 'string' ) key = BigInt( '0x' + key ) ; 
        if( typeof key != 'bigint' ) throw "sign: Invalid key format (HEX string or bigint expected)" ;
        
        const k = I.bigRand( 160 ) ;
        const k1 = I.pmod( k, I.q - 2n, I.q ) ;  // k^-1
        var r = I.pmod( I.g, k, I.p ) % I.q ;
        var s = ( ( hash + key * r ) * k1 ) % I.q ;
        return [ r.toString( 16 ), s.toString( 16 ) ] ;
    }

    I.check = function( hash, key, sign ) {
        if( typeof hash == 'string' ) hash = BigInt( '0x' + hash ) ; 
        if( typeof hash != 'bigint' ) throw "check: Invalid hash format (HEX string or bigint expected)" ;
        if( typeof key == 'string' ) key = BigInt( '0x' + key ) ; 
        if( typeof key != 'bigint' ) throw "check: Invalid key format (HEX string or bigint expected)" ;
        if( ! Array.isArray( sign ) ) throw "check: Invalid sign format (array expected)" ;
        if( sign.length != 2 ) throw "check: Invalid sign length (array[2] expected)" ;
        if( typeof sign[0] == 'string' ) sign[0] = BigInt( '0x' + sign[0] ) ; 
        if( typeof sign[1] == 'string' ) sign[1] = BigInt( '0x' + sign[1] ) ;
        if( typeof sign[0] != 'bigint' || typeof sign[1] != 'bigint' ) throw "check: Invalid sign[] format (HEX string or bigint expected)" ;
        var w = I.pmod( sign[1], I.q - 2n, I.q ) ;
        var u1 = ( hash * w ) % I.q ;
        var u2 = ( sign[0] * w ) % I.q ;
        var v = ( ( I.pmod( I.g, u1, I.p ) * I.pmod( key, u2, I.p ) ) % I.p ) % I.q ;
        return v == sign[0] ;
    }

    I.init() ;

    // var h = 2n ;
    // I.g = I.pmod( h, ( I.p - 1n ) / I.q, I.p ) ;
    

    /* var x = BigInt( "0x411602CB19A6CCC34494D79D98EF1E7ED5AF25F7" ) ;
     var y = I.pmod( I.g, x, I.p ) ;

    var h = BigInt( "0x8151325dcdbae9e0ff95f9f9658432dbedfdb209" ) ;  // sample
    // var h = BigInt( "0xa94a8fe5ccb19ba61c4c0873d391e987982fbbd3" ) ;  // test
    var k = BigInt( "0x7BDB6B0FF756E1BB5D53583EF979082F9AD5BD5B" ) ;
    var k1 = I.pmod( k, I.q - 2n, I.q ) ;  // k^-1
    var r = I.pmod( I.g, k, I.p ) % I.q ;
    var s = ( ( h + x * r ) * k1 ) % I.q ;
    

    var w = I.pmod( s, I.q - 2n, I.q ) ;    
    var u1 = ( h * w ) % I.q ;
    var u2 = ( r * w ) % I.q ;
    console.log(w, typeof w);
    console.log(u1, typeof u1);
    console.log(u2, typeof u2);
    var v = ( ( I.pmod( I.g, u1, I.p ) * I.pmod( y, u2, I.p ) ) % I.p ) % I.q ;
    console.log( v ) ;
console.log( r.toString( 16 ), v.toString( 16 ), r == v );*/


}
