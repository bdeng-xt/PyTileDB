import os,sys

import pandas as pd 
import pyarrow as pa 
import pytiledb as tdb 
import tiledbutil 

csv_columns=['tradingday','instrumentid','exchangeid','exchangeinstrid']
csv_columns.extend(['lastprice','presettlementprice','precloseprice','preopeninterest'])
csv_columns.extend(['openprice','highestprice','lowestprice','totvolume','totturnover','openinterest','closeprice'])
csv_columns.extend(['settlementprice','upperlimitprice','lowerlimitprice','tsrcv','currdelta'])
csv_columns.extend(['updatetime','updatemillisec'])
csv_columns.extend(['bidprice1','bidvolume1','askprice1','askvolume1'])
csv_columns.extend(['bidprice2','bidvolume2','askprice2','askvolume2'])
csv_columns.extend(['bidprice3','bidvolume3','askprice3','askvolume3'])
csv_columns.extend(['bidprice4','bidvolume4','askprice4','askvolume4'])
csv_columns.extend(['bidprice5','bidvolume5','askprice5','askvolume5'])
csv_columns.extend(['averageprice','actionday'])
ctpcsv_columns=['dt','ll']
ctpcsv_columns.extend(csv_columns)
def read_book_csv_to_df(csvfile='./data/20200318_day_INE_all_all_ctpbook.csv.gz'):
    df=None
    if csvfile is None or len(csvfile)==0:
        return df
    if csvfile.endswith('gz'):
        df=pd.read_csv(csvfile,header=None,compression='gzip')
    else:
        df=pd.read_csv(csvfile,header=None)
    df.columns=ctpcsv_columns 
    return df    

df=read_book_csv_to_df()
df=df.drop(['ll'],axis=1)

table=pa.Table.from_pandas(df)
datamap=tdb.ArrayUtil.get_columndatamap_from_pyarrow(table)
 
datamap.ncol() #number of columns
datamap.set_is_dim('tsrcv',True)
datamap.set_lower_bound('tsrcv',str(df['tsrcv'].min()))
datamap.set_upper_bound('tsrcv',str(df['tsrcv'].max()))


datamap.dimension_names()

uri='./tmp/bookdata'
tdb.ArrayUtil.write_from_columndatamap(uri,datamap,'')
 

 

