
/*
 * fmt_compile.h -- format types
 */

/* types that output text */
#define FT_COMP		1	/* the text of a component                 */
#define FT_COMPF	2	/* comp text, filled                       */
#define FT_LIT		3	/* literal text                            */
#define FT_LITF		4	/* literal text, filled                    */
#define FT_CHAR		5	/* a single ascii character                */
#define FT_NUM		6	/* "value" as decimal number               */
#define FT_NUMF		7	/* "value" as filled dec number            */
#define FT_STR		8	/* "str" as text                           */
#define FT_STRF		9	/* "str" as text, filled                   */
#define FT_STRFW	10	/* "str" as text, filled, width in "value" */
#define FT_STRLIT	11	/* "str" as text, no space compression     */
#define FT_STRLITZ	12	/* literal text with zero display width	   */
#define FT_PUTADDR	13	/* split and print address line            */

/* types that modify the "str" or "value" registers                     */
#define FT_LS_COMP	14	/* set "str" to component text          */
#define FT_LS_LIT	15	/* set "str" to literal text            */
#define FT_LS_GETENV	16	/* set "str" to getenv(text)            */
#define FT_LS_CFIND	17	/* set "str" to context_find(text)      */
#define FT_LS_DECODECOMP 18	/* set "str" to decoded component text  */
#define FT_LS_DECODE	19	/* decode "str" as RFC-2047 header	*/
#define FT_LS_TRIM	20	/* trim trailing white space from "str" */
#define FT_LV_COMP	21	/* set "value" to comp (as dec. num)    */
#define FT_LV_COMPFLAG	22	/* set "value" to comp flag word        */
#define FT_LV_LIT	23	/* set "value" to literal num           */
#define FT_LV_DAT	24	/* set "value" to dat[n]                */
#define FT_LV_STRLEN	25	/* set "value" to length of "str"       */
#define FT_LV_PLUS_L	26	/* set "value" += literal               */
#define FT_LV_MINUS_L	27	/* set "value" -= literal               */
#define FT_LV_DIVIDE_L	28	/* set "value" to value / literal       */
#define FT_LV_MODULO_L	29	/* set "value" to value % literal       */
#define FT_LV_CHAR_LEFT 30	/* set "value" to char left in output   */

#define FT_LS_MONTH	31	/* set "str" to tws month                   */
#define FT_LS_LMONTH	32	/* set "str" to long tws month              */
#define FT_LS_ZONE	33	/* set "str" to tws timezone                */
#define FT_LS_DAY	34	/* set "str" to tws weekday                 */
#define FT_LS_WEEKDAY	35	/* set "str" to long tws weekday            */
#define FT_LS_822DATE	36	/* set "str" to 822 date str                */
#define FT_LS_PRETTY	37	/* set "str" to pretty (?) date str         */
#define FT_LV_SEC	38	/* set "value" to tws second                */
#define FT_LV_MIN	39	/* set "value" to tws minute                */
#define FT_LV_HOUR	40	/* set "value" to tws hour                  */
#define FT_LV_MDAY	41	/* set "value" to tws day of month          */
#define FT_LV_MON	42	/* set "value" to tws month                 */
#define FT_LV_YEAR	43	/* set "value" to tws year                  */
#define FT_LV_YDAY	44	/* set "value" to tws day of year           */
#define FT_LV_WDAY	45	/* set "value" to tws weekday               */
#define FT_LV_ZONE	46	/* set "value" to tws timezone              */
#define FT_LV_CLOCK	47	/* set "value" to tws clock                 */
#define FT_LV_RCLOCK	48	/* set "value" to now - tws clock           */
#define FT_LV_DAYF	49	/* set "value" to tws day flag              */
#define FT_LV_DST	50	/* set "value" to tws daylight savings flag */
#define FT_LV_ZONEF	51	/* set "value" to tws timezone flag         */

#define FT_LS_PERS	52	/* set "str" to person part of addr    */
#define FT_LS_MBOX	53	/* set "str" to mbox part of addr      */
#define FT_LS_HOST	54	/* set "str" to host part of addr      */
#define FT_LS_PATH	55	/* set "str" to route part of addr     */
#define FT_LS_GNAME	56	/* set "str" to group part of addr     */
#define FT_LS_NOTE	57	/* set "str" to comment part of addr   */
#define FT_LS_ADDR	58	/* set "str" to mbox@host              */
#define FT_LS_822ADDR	59	/* set "str" to 822 format addr        */
#define FT_LS_FRIENDLY	60	/* set "str" to "friendly" format addr */
#define FT_LV_HOSTTYPE	61	/* set "value" to addr host type       */
#define FT_LV_INGRPF	62	/* set "value" to addr in-group flag   */
#define FT_LS_UNQUOTE	63	/* remove RFC 2822 quotes from "str"   */
#define FT_LV_NOHOSTF	64	/* set "value" to addr no-host flag */

/* Date Coercion */
#define FT_LOCALDATE	65	/* Coerce date to local timezone */
#define FT_GMTDATE	66	/* Coerce date to gmt            */

/* pre-format processing */
#define FT_PARSEDATE	67	/* parse comp into a date (tws) struct */
#define FT_PARSEADDR	68	/* parse comp into a mailaddr struct   */
#define FT_FORMATADDR	69	/* let external routine format addr    */
#define FT_CONCATADDR	70	/* formataddr w/out duplicate removal  */
#define FT_MYMBOX	71	/* do "mymbox" test on comp            */

/* conditionals & control flow (must be last) */
#define FT_SAVESTR	72	/* save current str reg               */
#define FT_DONE		73	/* stop formatting                    */
#define FT_PAUSE	74	/* pause                              */
#define FT_NOP		75	/* nop                                */
#define FT_GOTO		76	/* (relative) goto                    */
#define FT_IF_S_NULL	77	/* test if "str" null                 */
#define FT_IF_S		78	/* test if "str" non-null             */
#define FT_IF_V_EQ	79	/* test if "value" = literal          */
#define FT_IF_V_NE	80	/* test if "value" != literal         */
#define FT_IF_V_GT	81	/* test if "value" > literal          */
#define FT_IF_MATCH	82	/* test if "str" contains literal     */
#define FT_IF_AMATCH	83	/* test if "str" starts with literal  */
#define FT_S_NULL	84	/* V = 1 if "str" null                */
#define FT_S_NONNULL	85	/* V = 1 if "str" non-null            */
#define FT_V_EQ		86	/* V = 1 if "value" = literal         */
#define FT_V_NE		87	/* V = 1 if "value" != literal        */
#define FT_V_GT		88	/* V = 1 if "value" > literal         */
#define FT_V_MATCH	89	/* V = 1 if "str" contains literal    */
#define FT_V_AMATCH	90	/* V = 1 if "str" starts with literal */

#define IF_FUNCS FT_S_NULL	/* start of "if" functions */
