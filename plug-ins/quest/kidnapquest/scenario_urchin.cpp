/* $Id: scenario_urchin.cpp,v 1.1.2.16.6.3 2009/01/18 20:11:58 rufina Exp $
 *
 * ruffina, 2004
 */

#include "scenario_urchin.h"
#include "kidnapquest.h"

#include "pcharacter.h"
#include "npcharacter.h"
#include "object.h"
#include "act.h"
#include "clanreference.h"
#include "interp.h"
#include "merc.h"
#include "mercdb.h"
#include "def.h"

#define KS KidnapUrchinScenario

CLAN(battlerager);

bool KS::applicable( PCharacter *hero ) const
{
    return (hero->getClan( ) != clan_battlerager);
}

/*
 * hero messages
 */
void KS::msgRemoteReunion( NPCharacter *kid, NPCharacter *king, PCharacter *hero ) 
{
    act("$c1 хмуро смотрит на $C4.", kid, 0, king, TO_ROOM);
    hero->printf( "%s и %s уже встретились.\r\n", king->getNameP( '1' ).c_str( ), kid->getNameP( '1' ).c_str( ) );
    act("Приди к $C3 за благодарностью!", hero, 0, king, TO_CHAR);
}
void KS::msgKingDeath( NPCharacter *king, Character *killer, PCharacter *hero ) 
{
    if(hero == killer) {
        act("{YИдио$gт|т|тка.... Ты уби$gло|л|ла того, кто нуждался в твоей помощи.{x", killer, 0, 0, TO_CHAR);
        hero->send_to("{YЗадание отменяется.{x\r\n");
    } else {
        act("{Y$c1 подло убил того, кто нуждался в твоей помощи.{x", killer, 0, hero, TO_VICT);
        hero->send_to("{YЗадание отменяется.{x\r\n");
    }
}
void KS::msgKidDeath( NPCharacter *kid, Character *killer, PCharacter *hero ) 
{
    if(hero == killer) {
        act("{YИдио$gт|т|тка.... Ты уби$gло|л|ла того, кого долж$gно|ен|на бы$gло|л|ла спасти.{x", killer, 0, 0, TO_CHAR);
        hero->send_to("{YЗадание отменяется.{x\r\n");
    } else {
        act("{Y$c1 подло уби$gло|л|ла того, кого тебе было поручено спасти.{x", killer, 0, hero, TO_VICT);
        hero->send_to("{YЗадание отменяется.{x\r\n");
    }
}

/*
 * bandit actions
 */
void KS::actAttackHero( NPCharacter *bandit, PCharacter *hero ) 
{
    if (!hero->fighting) {
        act("$c1 произносит '{gЯ буду тебя воевать!{x'.", bandit, 0, hero, TO_ROOM);
    }
}
void KS::actBeginKidnap( NPCharacter *bandit, NPCharacter *kid ) 
{
    act("$c1 смотрит на белый билет, держа его вверх ногами.", bandit, 0, kid, TO_ROOM);
    act("$c1 произносит '{gЭту бумагу надо разъяснить{x'.", bandit, 0, kid, TO_ROOM);
    act("$c1 хватает $C4 за шиворот и тащит за собой.", bandit, 0, kid, TO_ROOM);
}
void KS::actHuntStep( NPCharacter *bandit ) 
{
    if(number_percent() < 10)
        act("$c1 до боли в затылке морщит узкий лоб.", bandit, 0, 0, TO_ROOM);
}
void KS::actKidnapStep( NPCharacter *bandit, NPCharacter *kid ) 
{
    if(number_percent() < 10)
        act("$c1 тащит сорванца за шиворот.", bandit, 0, 0, TO_ROOM);
}
void KS::actEmptyPath( NPCharacter *bandit, NPCharacter *kid ) 
{
    if(number_percent() < 10)
        act("$c1 стукается головой об стену.", bandit, 0, 0, TO_ROOM);
}

/*
 * king actions
 */
void KS::actLegend( NPCharacter *king, PCharacter *hero, KidnapQuest::Pointer quest ) 
{
    act("$c1 говорит тебе '{GМой сорванец сын сбежал из дома, спасаясь от призыва в клан Войнов.{x'", king, 0, hero, TO_VICT);
    act("$c1 говорит тебе '{GВы ведь знаете, туда в наши дни берут всех подряд.{x'", king, 0, hero, TO_VICT);
    act("$c1 говорит тебе '{GОтыщи его, пока он не попал в беду.{x'", king, 0, hero, TO_VICT);
    act("$c1 говорит тебе '{GСкорее всего он скрывается где-то в районе $t{x'", king, quest->princeArea.getValue( ).c_str( ), hero, TO_VICT);
}
void KS::actGiveMark( NPCharacter *king, PCharacter *hero, Object * mark, int time ) 
{
    char buf[MAX_STRING_LENGTH];
    

    act("$c1 говорит тебе '{GЯ продала все, что у меня было, чтобы купить этот белый билет...{x'", king, 0, hero, TO_VICT);
    act("$c1 вручает тебе $o4.", king, mark, hero, TO_VICT);
    act("$c1 вручает $C3 $o4.", king, mark, hero, TO_NOTVICT);
    act("$c1 говорит тебе '{GПередай его ему и поскорей!{x'", king, 0, hero, TO_VICT);
    sprintf( buf, "$c1 говорит тебе '{GМатеринское сердце подсказывает мне, "
                  "что, если ты не приведешь его ко мне через {Y%d{G минут%s, "
                  "с ним случится что-то непоправимое.{x'",
             time, GET_COUNT(time, "у", "ы", "") );

    act(buf, king, 0, hero, TO_VICT);
}
void KS::actMarkLost( NPCharacter *king, PCharacter *hero, Object * mark ) 
{
    act("$c1 говорит тебе '{GЧто ты надела$Gло|л|ла?!{x'", king, 0, hero, TO_VICT);
    act("$c1 говорит тебе '{GК счастью, такому олуху как ты я дала копию.{x'", king, 0, hero, TO_VICT);
    act("$c1 дает тебе новый $o4.", king, mark, hero, TO_VICT);
    act("$c1 дает $C3 новый $o4.", king, mark, hero, TO_NOTVICT);
}
void KS::actAckWaitComplete( NPCharacter *king, PCharacter *hero ) 
{
    act("$c1 чмокает тебя в обе щеки.", king, 0, hero, TO_VICT);
    act("$c1 чмокает $C4 в обе щеки.", king, 0, hero, TO_NOTVICT);
    act("$c1 говорит тебе: '{GИди скорее за наградой к тому, кто дал тебе задание!{x'.", king, 0, hero, TO_VICT);
}

/*
 * kid actions
 */
void KS::actHeroWait( NPCharacter *kid ) 
{
    if(number_percent( ) < 10)
        act("$c1 своим присутствием повышает в этом месте энтропию.", kid, 0, 0, TO_ROOM);
}
void KS::actNoHero( NPCharacter *kid, PCharacter *hero ) 
{
    if (number_percent( ) < 10 && hero && hero->in_room != kid->in_room)
        act("$c1 озирается в поисках $C2.", kid, 0, hero, TO_ROOM);
}
void KS::actHeroDetach( NPCharacter *kid, PCharacter *hero ) 
{
    if (hero)
        interpret_fmt( kid, "yell Эй, %s, ты где?!!!", hero->getNameP( ) );
}
void KS::actWrongGiver( NPCharacter *kid, Character *victim, Object *obj ) 
{
    act("$c1 безо всякого интереса смотрит на $o4.", kid, obj, 0, TO_ROOM);
}
void KS::actWrongMark( NPCharacter *kid, Character *victim, Object *obj ) 
{
    act("$c1 безо всякого интереса смотрит на $o4.", kid, obj, 0, TO_ROOM);
}
void KS::actGoodMark( NPCharacter *kid, Character *victim, Object *obj ) 
{
    interpret(kid, "grin");
    act("$c1 произносит '{gТеперь они до меня не доберутся!{x'", kid, 0, 0, TO_ROOM);
    act("$c1 произносит '{gПошли домой?{x'", kid, 0, 0, TO_ROOM);
}
void KS::actReunion( NPCharacter *kid, NPCharacter *king, PCharacter *hero ) 
{
    act("$c1 хмуро смотрит на $C4.", kid, 0, king, TO_ROOM);
    actAckWaitComplete(king, hero);
}
void KS::actBanditsUnleash( NPCharacter *kid, PCharacter *hero, NPCharacter *bandit ) 
{
    act("{YГруппа людей с суровыми лицами заковаными в латы преграждает тебе путь.{x", kid, 0, 0, TO_ROOM);
}
